
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
#define STATIC_IP 192,168,0,50 
IPAddress ip(STATIC_IP);   
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0); 
ESP8266WebServer server(80);
 // Indicates whether ESP has WiFi credentials saved from previous session.
bool initialConfig = false;
   

float t, tBME;
int p25, p10, h, p, s, id, hBME, pBME, counter = 1;
char tString[6];
char tBMEString[6];
char tTailString[6];
char tBMETailString[6];


bool status = true;

int lastCheck;

const int LED = D4; //2 Controls the onboard LED.
const int B1_PIN = D6; //12 Changing LCD pages.
const int B2_PIN = D3; //0 FLASH Button onboard, Start wifi config mode


 // Initialize the BME280 I2C
Adafruit_BME280 bme;

// Inicialize display LCD TFT 1.44" 
// Don't forget to update "User_Setup.h" in Bodmer libray for LCD pins
// ST7735_DRIVER and your type board
// TFT_WIDTH  128
// TFT_HEIGHT 128
// TFT_CS          PIN_D8
// TFT_DC          PIN_D0
// TFT_RST  -1     Reset pin on ESP8266

// D0_USED_FOR_DC  

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
  Wire.begin(D1, D2);
  bme.begin();
  get_BME();

  // Memory pool for JSON object tree.
  while (!Serial) continue;

  
   // Wi-Fi starting.
  WiFi.printDiag(Serial); //Remove this line if you do not want to see WiFi password printed
  if (WiFi.SSID()==""){
      Serial.println("No credentials, so get them now");
      tft.drawCentreString("No Credential,",64,25,1);
      tft.drawCentreString("So Get Them Now",64,40,1);
      tft.drawCentreString("STARTING",64,75,1);
      tft.drawCentreString("CONFIG MODE",64,90,1);
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
      tft.drawCentreString(WiFi.SSID(),64,10,2); // (Text,X,Y,Font)
      tft.setTextFont(1);
      tft.setCursor(28, 40); tft.println(WiFi.localIP());
      tft.setCursor(30, 55); tft.print(WiFi.channel()); tft.print("ch");
      tft.setCursor(63, 55); tft.print(WiFi.RSSI()); tft.print("dbm");
      tft.drawCentreString("Waiting",64, 85,1);
      tft.drawCentreString("Sensor Data",64, 105,1);
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
  } else if(counter == 4){
      Page4();
  }
}


void Page1() {
  get_BME();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.setCursor(5, 5); tft.print("IN");
  tft.setCursor(5, 70); tft.print("OUT");
  tft.setTextSize(1);
  tft.setCursor(110, 20); tft.print("O");
  tft.setCursor(110, 85); tft.print("O");
  tft.drawRightString(String(tBMEString[0])+String(tBMEString[1])+String(tBMEString[2]),95,20,6);
  tft.drawRightString(String(tString[0])+String(tString[1])+String(tString[2]),95,85,6);
  tft.drawString(String(tBMEString[3])+String(tBMEString[4]),95,37,4);
  tft.drawString(String(tString[3])+String(tString[4]),95,103,4);
}


void Page2() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.setCursor(5, 5); tft.print("PM 2.5");
  tft.setCursor(5, 70); tft.print("PM  10");

  if(p25 > 150 || p10 > 150) {
    colorPM = TFT_RED;
  } else if ((p25 > 50 && p25 < 150) || (p10 > 50 && p10 < 150)) {
    colorPM = TFT_ORANGE; 
  } else if(p25 < 50 || p10 < 50) {
    colorPM = TFT_WHITE;
  }
  tft.setTextFont(6);
  tft.setTextColor(colorPM);
  tft.drawRightString(String((int)p25),110,20,6);
  tft.drawRightString(String((int)p10),110,85,6);
}  


void Page3() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.setCursor(10, 5); tft.print("OUTDOOR");
  tft.setCursor(95, 25); tft.print("O");
  tft.drawRightString(String(tString), 90, 25, 4);
  tft.setTextFont(1);
  tft.setCursor(29, 60); tft.print("HUMID: "); tft.print(h); tft.print(" %");
  tft.setCursor(17, 75); tft.print("PRESURE: "); tft.print(p); tft.print(" hPa");
  tft.setCursor(24, 100); tft.print("WiFi S: "); tft.print(s); tft.print(" dBm");
}  


void Page4() {
  get_BME();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.setCursor(10, 5); tft.print("INDOOR");
  tft.setCursor(95, 25); tft.print("O");
  tft.drawRightString(String(tBMEString), 90, 25, 4);
  tft.setTextFont(1);
  tft.setCursor(29, 60); tft.print("HUMID: "); tft.print(hBME); tft.print(" %");
  tft.setCursor(17, 75); tft.print("PRESURE: "); tft.print(pBME); tft.print(" hPa");
  tft.setCursor(28, 100); tft.print(WiFi.localIP());
  tft.setCursor(28, 115); tft.print(WiFi.channel()); tft.print("ch");
  tft.setCursor(64, 115); tft.print(WiFi.RSSI()); tft.print("dBm");
}


 // Display LCD page for config mode.
void configModeCallback (WiFiManager *myWiFiManager) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(1);
  tft.drawCentreString("CONFIG MODE",64, 25, 1);
  tft.drawCentreString("START:",64, 40, 1);
  tft.setCursor(35, 75); tft.print(myWiFiManager->getConfigPortalSSID());
  delay(100);
  tft.setCursor(32, 90); tft.print(WiFi.softAPIP());
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
      if(counter >= 4){                //Number of pages
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
