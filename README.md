# Laufdaten.info Dust Sensor Indoor Display
Add-on indoor display for your [**laufdaten dust sensor**](https://luftdaten.info/en/home-en/)

If you are contributing to the [**luftdaten.info**](https://luftdaten.info/en/home-en/) project you can build your own indoor weather station and fetch the data off your outdoor sensor.
# How it works
Outside sensor sends information to the Laufdaten servers and to the indoor controller API that displays it on display by your choice. The display controller is connected to your local network with static IP configured from the .ino file (default 192.168.0.50).
The same IP Address you have to add in the outside sensor to send data to the indoor display controller. (More on that in the Configuration Tab) 

*Screenshots from 2.8"(background actually is black)*
![allpages](https://user-images.githubusercontent.com/22327641/38440072-c37853f0-39e8-11e8-9b3e-93d77d72195f.jpg)

# Getting Started
You will need:
  - Working [Laufdaten dust sensor](https://luftdaten.info/en/construction-manual/) **with BME 280 and SDS011**
  - *Another* NodeMCU v3 ESP8266
  - *Another* BME 280
  - A display
    - OLED 0.96" I2C interface
    - OLED 1.3" I2C interface
    - LCD TFT 1.44" SPI interface
    - LCD TFT 2.8"  SPI interface without touch
    
## Installing
  ##### Setting up the arduino IDE
  - Install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
  - Add ESP8266 Libraries
    To begin, we’ll need to update the board manager with a custom URL. Open up Arduino, then go to the Preferences (File > Preferences).       Then, towards the bottom of the window, copy this URL into the “Additional Board Manager URLs” text box:

     > http://arduino.esp8266.com/stable/package_esp8266com_index.json
   - Install the following libraries
      - [WifiManager by Ken Taylor](https://github.com/kentaylor/WiFiManager)
      - [Adafruit Sensors](https://github.com/adafruit/Adafruit_Sensor)
      - [Adafruit BME280](https://github.com/adafruit/Adafruit_BME280_Library)
      - LCD
        - [TFT_eSPI by Bodmer](https://github.com/Bodmer/TFT_eSPI)
      - OLED
        - [Driver library for the SSD1306 and SH1106 OLED by ThingPulse](https://github.com/ThingPulse/esp8266-oled-ssd1306)
        
  ##### Connect the hardware for Oled and LCD 1.44"
  - BME280 (I2C)
    - SDA -> D1
    - SDL -> D2
  - OLED (I2C)
    - SDA -> D1
    - SDL -> D2
  - LCD (SPI)
    - TFT_CS -> D8
    - TFT_DC -> D0
    - TFT_RST -> Reset pin
    - TFT_SCL -> D5
    - TFT_SDA -> D7
    - TFT_LED -> +3.3v
    - Make the appropriate changes to User_Setup.h in Bodmer library (by default on Windowns located in Documents/Arduino/libraries/TFT-eSPI/) according to your display. The User_Setup.h file is very well documented.
    - You can find ready User_Setup.h in code folders. For 1.44 if you have screen offset choose different board.
            
  - Buttons (Pin to GND)
    - D6 (Display page changing)
    - D3 (Configuration Mode -Onboard flash button)
  - You can look also schematic pdf in shields folder
  
  ##### Connect the hardware for LCD 2.80"
  - See schematic pdf in shields folder
  
##### Configure the Indoor Display Conroller
  - After uploading the code the controller will run in Configuration Mode automatically. To manually put the controller in config mode use the flash button. 
  - The device tries to connect to the configured WLAN access point. If this does not work, the controller opens an access point with the name "ESP *id*". The ID referes to the ChipID (ex. ESP12345). Connect to the new network, wait a moment until the connection is made. Sometimes it take multiple attempts.
  - Configure using browser
    - Open your browser and type in http://192.168.4.1/. You see the menu site, choose “Configure” and input your credentional.
    - After saving the desired configuration click on **EXIT PORTAL**! Else the configuration won't be saved.
  **OR**
  - Configure using android application. Special thanks to Keneth Taylor.
    - Download the [ESP Connect app](https://play.google.com/store/apps/details?id=au.com.umranium.espconnect) and follow the steps.
  - Oled version is without WiFi menager and you must add wifi SSID and Password in the code.  
  
##### Configure the OutsideSensor
  - Find laufdatens sensor IP Address.
  - Go to its IP Address (ex. 192.168.0.112)
  - Click on Configuration
  - Add the static IP of the indoor display controller (192.168.0.50 by default, standart router settings from 192.168.0.2 through 192.168.0.99 are not used for DHCP).
  - The path and the port as shown below.
<img width="308" alt="outdoor sensor settings" src="https://user-images.githubusercontent.com/22327641/38470807-d6eae57c-3b70-11e8-81f4-78d50c0c58cd.png">

## Shields
  - Kicad and Gerber files are in shields folder.
    - Indoor display
      - Oled 0.96 (Tested)
      - LCD 1.44  (Tested)
      - LCD 2.80  (ESP-12E tested)
    - Outdoor sensor for better connection between sensors and ESP.
      
          
