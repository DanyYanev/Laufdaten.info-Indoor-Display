
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include "SH1106.h"               //https://github.com/ThingPulse/esp8266-oled-ssd1306
#include "SSD1306.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define _TIMEOUT_ 1000

const char* ssid = "TP-LINK";
const char* password = "abcd1234";

 //set static ip
#define _STATIC_IP 192,168,0,50
IPAddress ip(_STATIC_IP);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0); 
ESP8266WebServer server(80);  

float t, tBME;
int p25, p10, h, p, s, id, hBME, pBME, counter = 1;
char tString[6];
char tBMEString[6];

bool status = true;

int lastCheck;

const int LED = D4; //2 Controls the onboard LED.
const int B1_PIN = D5; // 14 Button on shield, Changing Oled pages.
const int B2_PIN = D6; // 12 Button on shield, WiFi status of ESP


 // Initialize the BME280 I2C
Adafruit_BME280 bme;
#define BME_SDA D1
#define BME_SDL D2


 // Initialize the OLED display using Wire library
//SH1106 display(0x3c, D1, D2);
SSD1306  display(0x3c, D1, D2);


void setup(void){
  Serial.begin(115200);
  Serial.println("...");

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(B1_PIN, INPUT_PULLUP);
  pinMode(B2_PIN, INPUT_PULLUP);

    // BME280 Start.
  bme.begin();
  get_BME(); 

  
  // Memory pool for JSON object tree.
  while (!Serial) continue;
  
  
  
  // Wi-Fi starting.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 10, "Cant");
    display.drawString(64, 36, "Connect");
    display.display();
  }
    Serial.println("");
    Serial.print("Connected to: ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Channel is:  ");
    Serial.println(WiFi.channel());
    Serial.print("Signal is: ");
    Serial.println(WiFi.RSSI());  
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 1, WiFi.SSID());
    display.drawString(64, 24, WiFi.localIP().toString());
    display.drawString(64, 47, String(WiFi.channel()) + "ch"+"      " + String(WiFi.RSSI())+ "dbm");
    display.display();
    delay(3000);

  // mDNS server starting.
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Waiting sensor data...");

  lastCheck = millis();
}

void handleRoot() {
     if (server.hasArg("plain")== false){ //Check if body received
          server.send(200, "text/plain", "Body not received");
          return;
    }
    String message = "Body received: Json file\n";
           message += server.arg("plain");
           message += "\n";
    Serial.println(message);

    // JSON buffer size
    const size_t bufferSize = JSON_ARRAY_SIZE(9) + 9*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 420;
    DynamicJsonBuffer jsonBuffer(bufferSize);
   
    // JSON input string.
    String json = server.arg("plain");

    // Root of the object tree.
    JsonObject& root = jsonBuffer.parseObject(json);

    // Test if parsing succeeds.
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }

    // Fetch values from Json file.
    id = atoi(root["esp8266id"]); // ESP8266 ID number
    JsonArray& sensordatavalues = root["sensordatavalues"];
    for(auto sensor : sensordatavalues){
      if(strcmp("SDS_P1", sensor["value_type"].as<const char*>()) == 0){
        p10 = atoi(sensor["value"].as<const char*>()); 
      } else if(strcmp("SDS_P2", sensor["value_type"].as<const char*>()) == 0){
        p25 = atoi(sensor["value"].as<const char*>()); 
      } else if(strcmp("BME280_temperature", sensor["value_type"].as<const char*>()) == 0){
        t = atof(sensor["value"].as<const char*>()); 
      } else if(strcmp("BME280_humidity", sensor["value_type"].as<const char*>()) == 0){
        h = atoi(sensor["value"].as<const char*>()); 
      } else if(strcmp("BME280_pressure", sensor["value_type"].as<const char*>()) == 0){
        p = atoi(sensor["value"].as<const char*>()); 
        p /= 100;
      } else if(strcmp("signal", sensor["value_type"].as<const char*>()) == 0){
        s = atoi(sensor["value"].as<const char*>()); 
      }
    }
   
    // Turns numbers into text to reduce 1 digit after decimal point.
    dtostrf(t, 5, 1, tString);


  
    // Print values.
    Serial.print("ESP8266 ID: ");
    Serial.println(id);
    Serial.println(".");
    serialprintData();   
    
    server.send(200, "text/plain", "OK");    
}

// Ganerate function for BME sensor
void get_BME() {
    tBME = bme.readTemperature();
    hBME = bme.readHumidity();
    pBME = bme.readPressure()/100.0F;

    // Turns numbers into text to reduce 1 digit after decimal point.
    dtostrf(tBME, 5, 1, tBMEString);
}


void serialprintData() {
  get_BME(); 
  Serial.println("Indoor data"); 
  Serial.print("Temperture is: ");
  Serial.println(tBME);
  Serial.print("Humidity is: ");
  Serial.println(hBME);
  Serial.print("Presure is: ");
  Serial.println(pBME);
  Serial.println(".");
  Serial.println("Outdoor data");
  Serial.print("Temperture is: ");
  Serial.println(t);
  Serial.print("Humidity is: ");
  Serial.println(h);
  Serial.print("Presure is: ");
  Serial.println(p);  
  Serial.print("Dust PPM 2.5: ");
  Serial.println(p25);
  Serial.print("Dust PPM  10: ");
  Serial.println(p10); 
  Serial.print("Signal is: ");
  Serial.println(s);   
  Serial.println(".");
  Serial.println("Waiting sensor data");
  Serial.println(".");   
}

void OledDisplayPrint1() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(5, 1, "Temp: " + String(tString) + " °C");
    display.drawString(5, 24, "Humi:  " + String(h) + "  %");
    display.drawString(5, 47, "Pres: " + String(p) + " hPa");
    display.display();
    delay(100);
}

void OledDisplayPrint2() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(20, 1, "Dust sensor");
    display.drawString(5, 24, "P 2.5:  " + String(p25)+ " ppm");
    display.drawString(5, 47, "P  10:  " + String(p10)+ " ppm");
    display.display();
    delay(100);
}

void OledDisplayPrint3() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 10, "ID " + String(id));
    display.drawString(64, 36, "Signal  " + String(s) + "dbm");
    display.display();
    delay(100);
}

void OledDisplayPrint4() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(5, 1, "TempIn: " + String(tBMEString) + " °C");
    display.drawString(5, 24, "HumiIn:  " + String(hBME) + "  %");
    display.drawString(5, 47, "PresIn: " + String(pBME) + " hPa");
    display.display();
    delay(100);
}

// Ganerate Oled page for Wifi status
void OledDisplayPrint5() {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 1, WiFi.SSID());
    display.drawString(64, 24, WiFi.localIP().toString());
    display.drawString(64, 47, String(WiFi.channel()) + "ch"+"      " + String(WiFi.RSSI())+ "dbm");
    display.display();
    delay(100);
}

void loop(void){
   // Reset of ESP if wrong IP 
  if(WiFi.localIP() == IPAddress(_STATIC_IP)){
    server.handleClient();    
  } else {
    Serial.println(".");
    Serial.println("Wrong IP or no conection: Reset ESP");
    ESP.reset();
    delay(1000); 
  }
    // Waiting data from outside sensor.
  if(int(id) == 0){
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(64, 10, "Waiting");
    display.drawString(64, 36, "sensor data");
    display.display();
    } else {
       
      // Oled display pages changing with button1
    if(digitalRead(B1_PIN) == LOW){
      if(counter >= 4){
        counter = 1;
      } else {
        counter++;
      }
      Serial.print("Oled page ");
      Serial.println(counter);
      delay(200);
    }
     // Oled display page5 with button2
    if(digitalRead(B2_PIN) == LOW){
      OledDisplayPrint5();
      Serial.println("Oled page 5");
      delay(200);
      } else if(counter == 1){
          OledDisplayPrint1();
      } else if(counter == 2) {
          OledDisplayPrint2();
      } else if(counter == 3) {
          OledDisplayPrint3();
      } else if(counter == 4) {
          OledDisplayPrint4();
      }
  } 
  
   // Status of ESP8266
  if(millis() - lastCheck > _TIMEOUT_){
    if(status){
      digitalWrite(LED, LOW);  //turn on diode
      status = false;
    } else {
      digitalWrite(LED, HIGH); //turn off diode
      status = true;
    }
    lastCheck = millis();
  }
}
