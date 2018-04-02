EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:NodeMCU v3 AirbgDisplay V1.0 LCD1.44 BME280-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x04 J3
U 1 1 5A887D89
P 8800 2200
F 0 "J3" H 8800 2400 50  0000 C CNN
F 1 "BME280" H 8950 1900 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 8800 2200 50  0001 C CNN
F 3 "" H 8800 2200 50  0001 C CNN
	1    8800 2200
	1    0    0    -1  
$EndComp
Text GLabel 3950 1800 0    60   Input ~ 0
D1-SDA
Text GLabel 3950 1900 0    60   Input ~ 0
D2-SCL
Text GLabel 8600 2100 0    60   Input ~ 0
D1-SDA
Text GLabel 8600 2200 0    60   Input ~ 0
D2-SCL
$Comp
L GND #PWR14
U 1 1 5A88A4D3
P 8000 2300
F 0 "#PWR14" H 8000 2050 50  0001 C CNN
F 1 "GND" H 8000 2150 50  0000 C CNN
F 2 "" H 8000 2300 50  0001 C CNN
F 3 "" H 8000 2300 50  0001 C CNN
	1    8000 2300
	1    0    0    1   
$EndComp
$Comp
L +3.3V #PWR15
U 1 1 5A88A4F6
P 8000 2400
F 0 "#PWR15" H 8000 2250 50  0001 C CNN
F 1 "+3.3V" H 8000 2540 50  0000 C CNN
F 2 "" H 8000 2400 50  0001 C CNN
F 3 "" H 8000 2400 50  0001 C CNN
	1    8000 2400
	1    0    0    1   
$EndComp
$Comp
L +5V #PWR5
U 1 1 5A88ABC0
P 1750 3100
F 0 "#PWR5" H 1750 2950 50  0001 C CNN
F 1 "+5V" H 1750 3240 50  0000 C CNN
F 2 "" H 1750 3100 50  0001 C CNN
F 3 "" H 1750 3100 50  0001 C CNN
	1    1750 3100
	1    0    0    1   
$EndComp
Text Notes 4350 1750 2    60   ~ 0
D0\n
Text Notes 4600 1850 2    60   ~ 0
D1-SDA
Text Notes 4600 1950 2    60   ~ 0
D2-SCL
Text Notes 4350 2050 2    60   ~ 0
D3
Text Notes 4350 2150 2    60   ~ 0
D4
Text Notes 4350 2450 2    60   ~ 0
D5
Text Notes 4350 2550 2    60   ~ 0
D6
Text Notes 4350 2650 2    60   ~ 0
D7
Text Notes 4350 2750 2    60   ~ 0
D8
Text Notes 4350 2850 2    60   ~ 0
RX
Text Notes 4350 2950 2    60   ~ 0
TX
Text Notes 4400 3150 2    60   ~ 0
3.3V
Text Notes 4400 2350 2    60   ~ 0
GND
Text Notes 4400 3050 2    60   ~ 0
GND
Text Notes 9050 2350 2    60   ~ 0
GND
Text Notes 9050 2450 2    60   ~ 0
3.3V
Text Notes 9050 2250 2    60   ~ 0
SCL
Text Notes 9050 2150 2    60   ~ 0
SDA
Text Notes 2700 1750 2    60   ~ 0
A0
Text Notes 2700 3150 2    60   ~ 0
5V
Text Notes 2750 2250 2    60   ~ 0
SD1
Text Notes 2750 2150 2    60   ~ 0
SD2
Text Notes 2750 2050 2    60   ~ 0
SD3
Text Notes 2750 2350 2    60   ~ 0
CMD
Text Notes 2750 2450 2    60   ~ 0
SDO
Text Notes 2750 2550 2    60   ~ 0
CLK
Text Notes 2750 2750 2    60   ~ 0
3.3V
Text Notes 2750 2650 2    60   ~ 0
GND
Text Notes 2750 2950 2    60   ~ 0
RST
NoConn ~ 2300 2000
NoConn ~ 2300 2100
Text GLabel 3950 2600 0    60   Input ~ 0
SDA
Text GLabel 3950 2700 0    60   Input ~ 0
CS
$Comp
L SW_Push SW1
U 1 1 5A896733
P 3850 5200
F 0 "SW1" H 3900 5300 50  0000 L CNN
F 1 "D6-B1" H 3850 5140 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3850 5400 50  0001 C CNN
F 3 "" H 3850 5400 50  0001 C CNN
	1    3850 5200
	0    -1   -1   0   
$EndComp
Text GLabel 3950 2100 0    60   Input ~ 0
D4
NoConn ~ 2300 2300
NoConn ~ 2300 2200
Text GLabel 3950 2400 0    60   Input ~ 0
SCL
Text GLabel 2300 2900 0    60   Input ~ 0
RESET
NoConn ~ 2300 1700
$Comp
L LED D4
U 1 1 5A8DEA12
P 5700 5150
F 0 "D4" H 5700 5250 50  0000 C CNN
F 1 "LED" H 5700 5050 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 5700 5150 50  0001 C CNN
F 3 "" H 5700 5150 50  0001 C CNN
	1    5700 5150
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5A8DEA18
P 5700 5450
F 0 "R1" V 5780 5450 50  0000 C CNN
F 1 "220R" V 5700 5450 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5630 5450 50  0001 C CNN
F 3 "" H 5700 5450 50  0001 C CNN
	1    5700 5450
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x15 J1
U 1 1 5A8EC7ED
P 2500 2400
F 0 "J1" H 2500 3200 50  0000 C CNN
F 1 "J1" H 2500 1600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 2500 2400 50  0001 C CNN
F 3 "" H 2500 2400 50  0001 C CNN
	1    2500 2400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x15 J2
U 1 1 5A8EC8DD
P 4150 2400
F 0 "J2" H 4150 3200 50  0000 C CNN
F 1 "J2" H 4150 1600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 4150 2400 50  0001 C CNN
F 3 "" H 4150 2400 50  0001 C CNN
	1    4150 2400
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR8
U 1 1 5A8F1427
P 3400 2200
F 0 "#PWR8" H 3400 2050 50  0001 C CNN
F 1 "+3.3V" H 3400 2340 50  0000 C CNN
F 2 "" H 3400 2200 50  0001 C CNN
F 3 "" H 3400 2200 50  0001 C CNN
	1    3400 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR3
U 1 1 5A8F1617
P 1750 2700
F 0 "#PWR3" H 1750 2550 50  0001 C CNN
F 1 "+3.3V" H 1750 2840 50  0000 C CNN
F 2 "" H 1750 2700 50  0001 C CNN
F 3 "" H 1750 2700 50  0001 C CNN
	1    1750 2700
	1    0    0    -1  
$EndComp
Text Notes 4400 2250 2    60   ~ 0
3.3V
$Comp
L GND #PWR4
U 1 1 5A8F1B20
P 1750 3000
F 0 "#PWR4" H 1750 2750 50  0001 C CNN
F 1 "GND" H 1750 2850 50  0000 C CNN
F 2 "" H 1750 3000 50  0001 C CNN
F 3 "" H 1750 3000 50  0001 C CNN
	1    1750 3000
	1    0    0    1   
$EndComp
Text Notes 2750 3050 2    60   ~ 0
GND
Text Notes 2700 2850 2    60   ~ 0
EN
Text Notes 2700 1950 2    60   ~ 0
5V
Text Notes 2750 1850 2    60   ~ 0
GND
NoConn ~ 2300 2400
NoConn ~ 2300 2500
$Comp
L +5V #PWR2
U 1 1 5A8F2672
P 1750 1900
F 0 "#PWR2" H 1750 1750 50  0001 C CNN
F 1 "+5V" H 1750 2040 50  0000 C CNN
F 2 "" H 1750 1900 50  0001 C CNN
F 3 "" H 1750 1900 50  0001 C CNN
	1    1750 1900
	1    0    0    1   
$EndComp
$Comp
L GND #PWR1
U 1 1 5A8F267E
P 1750 1800
F 0 "#PWR1" H 1750 1550 50  0001 C CNN
F 1 "GND" H 1750 1650 50  0000 C CNN
F 2 "" H 1750 1800 50  0001 C CNN
F 3 "" H 1750 1800 50  0001 C CNN
	1    1750 1800
	1    0    0    1   
$EndComp
$Comp
L GND #PWR9
U 1 1 5A8F471A
P 3400 3000
F 0 "#PWR9" H 3400 2750 50  0001 C CNN
F 1 "GND" H 3400 2850 50  0000 C CNN
F 2 "" H 3400 3000 50  0001 C CNN
F 3 "" H 3400 3000 50  0001 C CNN
	1    3400 3000
	1    0    0    1   
$EndComp
NoConn ~ 2300 2800
Text GLabel 5700 5000 1    60   Input ~ 0
D4
Text GLabel 3950 2000 0    60   Input ~ 0
D3
NoConn ~ 2300 2600
NoConn ~ 3950 2800
NoConn ~ 3950 2900
$Comp
L Conn_01x08 J4
U 1 1 5AAD38E6
P 6750 2250
F 0 "J4" H 6750 2650 50  0000 C CNN
F 1 "SPI Display" H 6750 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 6750 2250 50  0001 C CNN
F 3 "" H 6750 2250 50  0001 C CNN
	1    6750 2250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR11
U 1 1 5AAD3D6B
P 6000 1950
F 0 "#PWR11" H 6000 1800 50  0001 C CNN
F 1 "+3.3V" H 6000 2090 50  0000 C CNN
F 2 "" H 6000 1950 50  0001 C CNN
F 3 "" H 6000 1950 50  0001 C CNN
	1    6000 1950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR13
U 1 1 5AAD3D88
P 6000 2650
F 0 "#PWR13" H 6000 2500 50  0001 C CNN
F 1 "+3.3V" H 6000 2790 50  0000 C CNN
F 2 "" H 6000 2650 50  0001 C CNN
F 3 "" H 6000 2650 50  0001 C CNN
	1    6000 2650
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR12
U 1 1 5AAD3DCD
P 6000 2050
F 0 "#PWR12" H 6000 1800 50  0001 C CNN
F 1 "GND" H 6000 1900 50  0000 C CNN
F 2 "" H 6000 2050 50  0001 C CNN
F 3 "" H 6000 2050 50  0001 C CNN
	1    6000 2050
	-1   0    0    -1  
$EndComp
Text GLabel 6550 2150 0    60   Input ~ 0
CS
Text GLabel 6550 2450 0    60   Input ~ 0
SDA
Text GLabel 6550 2250 0    60   Input ~ 0
RESET
Text GLabel 6550 2550 0    60   Input ~ 0
SCL
Text GLabel 3950 1700 0    60   Input ~ 0
A0/DC
Text GLabel 6550 2350 0    60   Input ~ 0
A0/DC
Text Notes 7050 2100 2    60   ~ 0
GND
Text Notes 7050 2000 2    60   ~ 0
3.3V
Text Notes 7050 2700 2    60   ~ 0
LED
Text Notes 7000 2200 2    60   ~ 0
CS
Text Notes 7100 2300 2    60   ~ 0
RESET
Text Notes 7100 2400 2    60   ~ 0
A0/DC
Text Notes 7050 2500 2    60   ~ 0
SDA
Text Notes 7050 2600 2    60   ~ 0
SCL
Wire Wire Line
	8000 2300 8600 2300
Wire Wire Line
	8000 2400 8600 2400
Wire Wire Line
	3950 2200 3400 2200
Wire Wire Line
	2300 3000 1750 3000
Wire Wire Line
	2300 2700 1750 2700
Wire Wire Line
	2300 1800 1750 1800
Wire Wire Line
	3950 3000 3400 3000
Connection ~ 1750 1900
Connection ~ 1750 3100
Wire Wire Line
	6550 1950 6000 1950
Wire Wire Line
	6550 2650 6000 2650
Wire Wire Line
	6550 2050 6000 2050
Wire Wire Line
	1750 1900 2300 1900
Wire Wire Line
	1750 3100 2300 3100
$Comp
L +3.3V #PWR10
U 1 1 5AAD42DA
P 3400 3100
F 0 "#PWR10" H 3400 2950 50  0001 C CNN
F 1 "+3.3V" H 3400 3240 50  0000 C CNN
F 2 "" H 3400 3100 50  0001 C CNN
F 3 "" H 3400 3100 50  0001 C CNN
	1    3400 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 3100 3400 3100
$Comp
L Conn_01x02 J5
U 1 1 5AAD58B8
P 10450 2150
F 0 "J5" H 10450 2250 50  0000 C CNN
F 1 "5V IN" H 10450 1950 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_S02B-XH-A_02x2.50mm_Angled" H 10450 2150 50  0001 C CNN
F 3 "" H 10450 2150 50  0001 C CNN
	1    10450 2150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5AAD5F43
P 9700 2250
F 0 "#PWR?" H 9700 2100 50  0001 C CNN
F 1 "+5V" H 9700 2390 50  0000 C CNN
F 2 "" H 9700 2250 50  0001 C CNN
F 3 "" H 9700 2250 50  0001 C CNN
	1    9700 2250
	1    0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5AAD5F49
P 9700 2150
F 0 "#PWR?" H 9700 1900 50  0001 C CNN
F 1 "GND" H 9700 2000 50  0000 C CNN
F 2 "" H 9700 2150 50  0001 C CNN
F 3 "" H 9700 2150 50  0001 C CNN
	1    9700 2150
	1    0    0    1   
$EndComp
Wire Wire Line
	10250 2150 9700 2150
Connection ~ 9700 2250
Wire Wire Line
	9700 2250 10250 2250
$Comp
L SW_Push SW2
U 1 1 5AAE64FB
P 1900 5200
F 0 "SW2" H 1950 5300 50  0000 L CNN
F 1 "D3-B2" H 1900 5140 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 1900 5400 50  0001 C CNN
F 3 "" H 1900 5400 50  0001 C CNN
	1    1900 5200
	0    -1   -1   0   
$EndComp
Text GLabel 1900 5000 1    60   Input ~ 0
D3
Text GLabel 3950 2500 0    60   Input ~ 0
D6
Text GLabel 3850 5000 1    60   Input ~ 0
D6
$Comp
L GND #PWR?
U 1 1 5AB8F392
P 3850 5400
F 0 "#PWR?" H 3850 5150 50  0001 C CNN
F 1 "GND" H 3850 5250 50  0000 C CNN
F 2 "" H 3850 5400 50  0001 C CNN
F 3 "" H 3850 5400 50  0001 C CNN
	1    3850 5400
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5AB8F42A
P 1900 5400
F 0 "#PWR?" H 1900 5150 50  0001 C CNN
F 1 "GND" H 1900 5250 50  0000 C CNN
F 2 "" H 1900 5400 50  0001 C CNN
F 3 "" H 1900 5400 50  0001 C CNN
	1    1900 5400
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5AB8F474
P 5700 5600
F 0 "#PWR?" H 5700 5450 50  0001 C CNN
F 1 "+5V" H 5700 5740 50  0000 C CNN
F 2 "" H 5700 5600 50  0001 C CNN
F 3 "" H 5700 5600 50  0001 C CNN
	1    5700 5600
	1    0    0    1   
$EndComp
Text Notes 2300 1250 0    118  ~ 24
ESP8266 NodeMCU V3
Text Notes 5900 1250 0    118  ~ 24
LCD TFT 1.44"
Text Notes 8000 1250 0    118  ~ 24
BME 280
Text Notes 950  4600 0    79   ~ 16
         Config Mode\nParallel to onboard Flash Button\n
Text Notes 3500 4500 0    79   ~ 16
Page Button
Text Notes 5000 4600 0    79   ~ 16
      Shield LED\nParallel to built in LED
Text Notes 9650 1350 0    118  ~ 24
 External \nshield PS
$EndSCHEMATC
