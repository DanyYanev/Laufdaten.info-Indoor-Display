# Laufdaten.info Dust Sensor Indoor Display
Add-on indoor display for your [**laufdaten.info**](https://luftdaten.info/en/home-en/) Dust Sensor

If you are contributing to the [**luftdaten.info**](https://luftdaten.info/en/home-en/) project you can build your own indoor weather station and fetch the data off your outdoor sensor.

<img width="960" alt="allpagestogether" src="https://user-images.githubusercontent.com/22327641/38211441-255999e0-36c3-11e8-91c3-3e0c0eaa3495.png">

# Getting Started
You will need:
  - Working and setup [OK Lab Stuttgard Device](https://luftdaten.info/en/construction-manual/)
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
        
    - Connect the hardware
