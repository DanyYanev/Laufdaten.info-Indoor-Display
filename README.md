# Laufdaten.info Dust Sensor Indoor Display
Add-on indoor display for your [**laufdaten.info**](https://luftdaten.info/en/home-en/) Dust Sensor

If you are contributing to the [**luftdaten.info**](https://luftdaten.info/en/home-en/) project you can build your own indoor weather station and fetch the data off your outdoor sensor.
# How it works
Outside sensor sends information to the Laufdaten servers and to the indoor controller API that displays it on display by your choice. The display controller is connected to your local network with static IP configured from the .ino file (default 192.168.0.50).
The same IP Address you have to add in the outside sensor to send data to the display controller. (More on that in the Configuration Tab) 

<img width="960" alt="allpagestogether" src="https://user-images.githubusercontent.com/22327641/38211441-255999e0-36c3-11e8-91c3-3e0c0eaa3495.png">

# Getting Started
You will need:
  - Working [OK Lab Stuttgard Device](https://luftdaten.info/en/construction-manual/) **with BME 280 and SDS011**
  - *Another* NodeMCU v3 ESP8266
  - *Another* BME 280
  - A display
    - OLED 0.96"
    - OLED 1.3"
    - LCD TFT 1.44"
    - LCD TFT 2.8"
    
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
        - [Driver library for the SSD1306 and SH1106 OLED](https://github.com/ThingPulse/esp8266-oled-ssd1306)
        
  ##### Connect the hardware
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
    - Make the appropriate changes to User_Setup.h in Bodmer library (by default on Windowns located in Documents/Arduino/libraries/TFT-eSPI/) according to your display. The User_Setup.h file is very well documented.
            
  - Buttons (Pin to GND)
    - D6 (Page changing)
    - D3 (Onboard flash button)
##### Configure the Indoor Display Conroller
  - After uploading the code the controller will run in Configuration Mode automatically. To manually put the controller in config mode use the flash button. 
  - Connect the station with the power cable
  - The station tries to connect to the configured WLAN access point. If this does not work, the sensor opens an access point with the name "ESP *id*". The ID referes to the ChipID (in the example below the 13562701). Connect to the new network, wait a moment until the connection is made. Sometimes it take multiple attempts.
  - Configure using browser
    - Open your browser and type in http://192.168.4.1/. You see the menu site, choose “Configure”.
    - After saving the desired configuration click on **EXIT PORTAL**! Else the configuration won't be saved.
  **OR**
  - Configure using android application. Special thanks to Keneth Taylor.
    - Download the [ESP Connect app](https://play.google.com/store/apps/details?id=au.com.umranium.espconnect) and follow the steps. 
  
##### Configure the OutsideSensor
  - Find laufdatens sensor IP Address.
  - Go to its IP Address (ex. 192.168.0.112)
  - Click on Configuration
  - Add the static IP of the indoor display controller (192.168.0.50 by default, standart router settings from 192.168.0.2 through 192.168.0.99 are not used for DHCP), the root and the port as shown below.
<img width="499" alt="outsidesensorsetup" src="https://user-images.githubusercontent.com/22327641/38430433-edc76c00-39c9-11e8-8d26-daefe53866ab.png">

      
          
