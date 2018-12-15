
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiManager.h>     //https://github.com/kentaylor/WiFiManager
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h> // https://github.com/Bodmer/TFT_eSPI
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define _TIMEOUT_ 1000

 //set static ip
#define STATIC_IP 192,168,1,50 
IPAddress ip(STATIC_IP);   
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0); 
ESP8266WebServer server(80);
 // Indicates whether ESP has WiFi credentials saved from previous session.
bool initialConfig = false;
   

float t, tBME;
int p25, p10, h, p, s, id, hBME, pBME, counter = 1;
char tString[6];
char tBMEString[6];

bool status = true;

int lastCheck;

const int LED = D4; //2 Controls the onboard LED.
const int B1_PIN = D2; //12 Changing LCD pages.
const int B2_PIN = D6; //Start wifi config mode or D3 to use FLASH Button onboard.


 // Initialize the BME280 I2C
Adafruit_BME280 bme;

// Inicialize display LCD TFT 2.8" 
// Display SCK       to NodeMCU pin D5
// Display SDO/MISO  to NodeMCU pin D6
// Display SDI/MOSI  to NodeMCU pin D7
// Display RESET     to NodeMCU pin RST

// Don't forget to update "User_Setup.h" in Bodmer libray for LCD pins
// ILI9341_DRIVER
// TFT_CS          PIN_D8
// TFT_DC          PIN_D0
// TFT_RST  -1     Reset pin on ESP8266

// D0_USED_FOR_DC  

#define TFT_WHITE  0xFFBB // New colour RGB565 code (warm white)
uint16_t colorPM;


TFT_eSPI tft = TFT_eSPI();  // Invoke library


void setup(void){
  Serial.begin(115200);
  Serial.println("...");
  
  // TFT LCD Start.
  tft.init();
  tft.setRotation(0);             //0,1,2,3
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
 
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(B1_PIN, INPUT_PULLUP);
  pinMode(B2_PIN, INPUT_PULLUP);
  
  // BME280 Start.
  Wire.begin(D1, D3);
  bme.begin();
  get_BME(); 
  

  // Memory pool for JSON object tree.
  while (!Serial) continue;

  
   // Wi-Fi starting.
  WiFi.printDiag(Serial); //Remove this line if you do not want to see WiFi password printed
  if (WiFi.SSID()==""){
      Serial.println("No credentials, so get them now");
      tft.drawCentreString("No Credential,",120,40,4);
      tft.drawCentreString("So Get Them Now",120,70,4);
      tft.drawCentreString("Starting",120,180,4);
      tft.drawCentreString("Config Mode",120,210,4);
      delay(2000);      
      initialConfig = true;
   } else {
      digitalWrite(LED, HIGH);          // Turn led off as we are not in configuration mode.
      WiFi.mode(WIFI_STA);              // Force to station mode because if device was switched off while in access point mode it will start up next time in access point mode.
      WiFi.config(ip, gateway, subnet); // For static IP
      unsigned long startedAt = millis();
      Serial.print("After waiting ");
      int connRes = WiFi.waitForConnectResult();
      float waited = (millis()- startedAt);
      Serial.print(waited/1000);
      Serial.println(" secs in setup()  ");
      Serial.print("connection result is: ");
      Serial.println(connRes);
      Serial.print("IP address is: ");
      Serial.println(WiFi.localIP());
      Serial.println(".");

      tft.setTextSize(1);
      tft.drawCentreString(WiFi.SSID(),120,30,4); // (Text,X,Y,Font)
      tft.setTextFont(4);
      tft.setCursor(50, 80); tft.println(WiFi.localIP());
      tft.setCursor(40, 110); tft.print(WiFi.channel()); tft.print("ch");
      tft.setCursor(115, 110); tft.print(WiFi.RSSI()); tft.print("dbm");
      tft.drawCentreString("Waiting",120,200,4);
      tft.drawCentreString("Sensor Data",120,230,4);
  }

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

    // Separating temperature digits to print with different size.
    dtostrf(t, 5, 1, tString);
  
    // Print values.
    Serial.print("ESP8266 ID: ");
    Serial.println(id);
    Serial.println(".");
    serialprintData();
    tftprintData();
            
    server.send(200, "text/plain", "OK");    
}


// Ganerate function for BME sensor
void get_BME() {
    tBME = bme.readTemperature();
    hBME = bme.readHumidity();
    pBME = bme.readPressure()/100.0F;

    // Separating temperature digits to print with different size.
    dtostrf(tBME, 5, 1, tBMEString);
}


// Ganerate function for serial print.
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
  Serial.println("Waiting station data");
  Serial.println(".");   
}


// Ganerate function for display pages.
void tftprintData() {
  if(counter == 1){
      Page1();
  } else if(counter == 2){
      Page2();
  } else if(counter == 3){
      Page3();
  } 
}


void Page1() {
  get_BME();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(5, 5); tft.print("IN");
  tft.setCursor(5, 120); tft.print("OUT");
  tft.setCursor(205, 25); tft.print("o");
  tft.setCursor(205, 140); tft.print("o");
  tft.drawRightString(String(tBMEString[0])+String(tBMEString[1])+String(tBMEString[2]),180,25,8);
  tft.drawRightString(String(tString[0])+String(tString[1])+String(tString[2]),180,140,8);
  tft.drawString(String(tBMEString[3])+String(tBMEString[4]),180,63,6);
  tft.drawString(String(tString[3])+String(tString[4]),180,178,6);
  
  tft.drawLine(80, 120, 225, 120, TFT_LIGHTGREY); //(x1, y1, x2, y2, color);
  tft.drawLine(10, 235, 230, 235, TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(20, 250); tft.print("PM 2.5:");
  tft.setCursor(20, 285); tft.print("PM  10:");
  tft.drawString(" ug/M",183,255,2);
  tft.drawString(" ug/M",183,290,2);
  
  if(p25 > 150 || p10 > 150) {
    colorPM = TFT_RED;
  } else if ((p25 > 50 && p25 < 150) || (p10 > 50 && p10 < 150)) {
    colorPM = TFT_ORANGE; 
  } else if(p25 < 50 || p10 < 50) {
    colorPM = TFT_WHITE;
  }
  tft.setTextColor(colorPM);
  tft.setCursor(135, 250); tft.print(p25);
  tft.setCursor(135, 285); tft.print(p10); 
}


void Page2() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(5, 5); tft.print("IN");
  tft.setCursor(205, 25); tft.print("o");
  tft.drawRightString(String(tBMEString[0])+String(tBMEString[1])+String(tBMEString[2]),180,25,8);
  tft.drawString(String(tBMEString[3])+String(tBMEString[4]),180,63,6);
  
  tft.drawLine(15, 120, 225, 120, TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(25, 133); tft.print("HUMID:   "); tft.print(hBME); tft.print("  %");
  tft.setCursor(25, 163); tft.print("PRES:     "); tft.print(pBME); tft.print(" hPa");
  
  tft.drawLine(15, 195, 225, 195, TFT_WHITE);
  tft.drawCentreString(WiFi.SSID(),120,208,4);
  tft.setCursor(50, 238); tft.println(WiFi.localIP());

  tft.drawLine(15, 271, 225, 271, TFT_WHITE);
  tft.setCursor(40, 285); tft.print(WiFi.channel()); tft.print("ch");
  tft.setCursor(115, 285); tft.print(WiFi.RSSI()); tft.print("dbm");
}  


void Page3() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(5, 5); tft.print("OUT");
  tft.setCursor(205, 25); tft.print("o");
  tft.drawRightString(String(tString[0])+String(tString[1])+String(tString[2]),180,25,8);
  tft.drawString(String(tString[3])+String(tString[4]),180,63,6);
  
  tft.drawLine(15, 120, 225, 120, TFT_WHITE);
  tft.setTextFont(4);
  tft.setCursor(25, 133); tft.print("HUMID:   "); tft.print(h); tft.print("  %");
  tft.setCursor(25, 163); tft.print("PRES:     "); tft.print(p); tft.print(" hPa");
  
  tft.drawLine(22, 195, 218, 195, TFT_LIGHTGREY);
  tft.setCursor(25, 208); tft.print("PM 2.5:");
  tft.setCursor(25, 238); tft.print("PM  10:");
  tft.drawString(" ug/M",180,213,2);
  tft.drawString(" ug/M",180,243,2);
  
  if(p25 > 150 || p10 > 150) {
    colorPM = TFT_RED;
  } else if ((p25 > 50 && p25 < 150) || (p10 > 50 && p10 < 150)) {
    colorPM = TFT_ORANGE; 
  } else if(p25 < 50 || p10 < 50) {
    colorPM = TFT_WHITE;
  }
  tft.setTextColor(colorPM);
  tft.setCursor(130, 208); tft.print(p25);
  tft.setCursor(130, 238); tft.print(p10);
  
  tft.drawLine(15, 270, 225, 270, TFT_WHITE);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(17, 285); tft.print("WIFI Sig : "); tft.print(s); tft.print(" dBm");
}  


 // Display LCD page for config mode.
void configModeCallback (WiFiManager *myWiFiManager) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawCentreString("Cofiguration",120,40,4);
  tft.drawCentreString(" Mode Start:",120,70,4);
  tft.drawCentreString(myWiFiManager->getConfigPortalSSID(),120,180,4);
  delay(100);
  tft.setTextFont(4);
  tft.setCursor(50, 210); tft.print(WiFi.softAPIP());
}


void loop(void){
  
    // If configuration portal requested?
  if ((digitalRead(B2_PIN) == LOW) || (initialConfig)) {
    server.close(); //Stop previous server
    Serial.println("Configuration portal requested.");
    digitalWrite(LED, LOW);
    WiFiManager wifiManager;
    
    //reset settings - for testing
    //wifiManager.resetSettings();
   
    wifiManager.setAPCallback(configModeCallback);
    if (!wifiManager.startConfigPortal()) {
      Serial.println("Not connected to WiFi but continuing anyway.");
    } else {
      Serial.println("Connected to WiFi.");
    }
     digitalWrite(LED, HIGH);
     Serial.println("WM: Reset ESP"); 
     ESP.reset();
     delay(5000);  
  }
  
    // Reset of ESP if wrong IP address.
  if(WiFi.localIP() == IPAddress(STATIC_IP)) {
    server.handleClient();    
  } else {
    Serial.println(".");
    Serial.println("Wrong IP: Reset ESP");
    ESP.reset();
    delay(1000);
  }  

  //if(id != 0){                       // When receive ESP ID from sensor
     if(digitalRead(B1_PIN) == LOW){   // LCD display pages changing with button 1
      if(counter >= 3){                //Number of pages
        counter = 1;
      } else {
        counter++;
      }
      Serial.println(".");
      Serial.print("LCD page ");
      Serial.println(counter);
      tftprintData();
      delay(200);        
    }
   //}
  
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
