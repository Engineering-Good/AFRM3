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
LIBS:arduino
LIBS:motordriver
LIBS:motor_encoder
LIBS:qtr-1a
LIBS:AFRM3-cache
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
L +6V #PWR1
U 1 1 5AA41E5D
P 4100 2800
F 0 "#PWR1" H 4100 2650 50  0001 C CNN
F 1 "+6V" H 4100 2940 50  0000 C CNN
F 2 "" H 4100 2800 50  0001 C CNN
F 3 "" H 4100 2800 50  0001 C CNN
	1    4100 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5AA41E9A
P 4100 2900
F 0 "#PWR2" H 4100 2650 50  0001 C CNN
F 1 "GND" H 4100 2750 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	1    0    0    -1  
$EndComp
$Comp
L Audio-Jack-2 J1
U 1 1 5AA41F3B
P 6800 4650
F 0 "J1" H 6775 4725 50  0000 C CNN
F 1 "Audio-Jack-2" H 6775 4475 50  0000 C CNN
F 2 "" H 7050 4650 50  0001 C CNN
F 3 "" H 7050 4650 50  0001 C CNN
	1    6800 4650
	-1   0    0    -1  
$EndComp
Text Notes 6950 4300 0    60   ~ 0
Direction:\n1: Up (I)\n2: None (O)\n4: Down (II)
Text Notes 7350 7500 0    60   ~ 0
AFRM3 w/ DRV8833
Text Notes 10600 7650 0    60   ~ 0
0.9
$Comp
L ArduinoNano U2
U 1 1 5AA43287
P 5100 4050
F 0 "U2" V 5150 3650 50  0000 C CNN
F 1 "ArduinoNano" V 5000 3650 50  0000 C CNN
F 2 "" V 5030 4050 50  0001 C CNN
F 3 "" H 5100 4050 50  0001 C CNN
	1    5100 4050
	1    0    0    -1  
$EndComp
Text Notes 8150 7650 0    60   ~ 0
05 May 2018
$Comp
L SW_SP3T SW2
U 1 1 5AA42113
P 6800 4400
F 0 "SW2" H 6800 4550 50  0000 C CNN
F 1 "SW_SP3T" H 7200 4400 50  0000 C CNN
F 2 "" H 6175 4575 50  0001 C CNN
F 3 "" H 6175 4575 50  0001 C CNN
	1    6800 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5500 3900 5900 3900
Wire Wire Line
	5500 4000 6000 4000
Wire Wire Line
	5500 4100 6100 4100
Wire Wire Line
	4300 5100 4700 5100
Wire Wire Line
	5500 4300 6600 4300
Wire Wire Line
	5500 4400 6200 4400
Wire Wire Line
	6200 4400 6200 4500
Wire Wire Line
	6200 4500 6600 4500
Wire Wire Line
	6100 4650 6600 4650
Wire Wire Line
	6100 4500 6100 4650
Wire Wire Line
	5500 4500 6100 4500
NoConn ~ 6600 4400
NoConn ~ 5500 3800
NoConn ~ 5500 4600
NoConn ~ 5500 5000
NoConn ~ 5500 5100
NoConn ~ 5500 5200
NoConn ~ 4700 5000
NoConn ~ 4700 4800
NoConn ~ 4700 4700
NoConn ~ 4700 4600
NoConn ~ 4700 4500
NoConn ~ 4700 4400
NoConn ~ 4700 4300
NoConn ~ 4700 4100
NoConn ~ 4700 4000
NoConn ~ 4700 3900
NoConn ~ 4700 3800
Wire Wire Line
	6400 4750 6600 4750
Wire Wire Line
	7050 4400 7000 4400
NoConn ~ 5500 4200
Wire Wire Line
	4400 5200 4700 5200
Wire Wire Line
	5500 4900 7050 4900
$Comp
L DRV8833-Module U1
U 1 1 5ACFAB70
P 6700 3850
F 0 "U1" H 6700 3750 60  0000 C CNN
F 1 "DRV8833-Module" H 6700 3850 60  0000 C CNN
F 2 "" H 6700 3850 60  0001 C CNN
F 3 "" H 6700 3850 60  0001 C CNN
	1    6700 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3300 6200 3400
Wire Wire Line
	6200 3200 6100 3200
Wire Wire Line
	6100 3200 6100 4100
Wire Wire Line
	6100 3500 6200 3500
Connection ~ 6100 3500
Wire Wire Line
	6000 4000 6000 3350
Wire Wire Line
	6000 3350 6200 3350
Connection ~ 6200 3350
Wire Wire Line
	5900 3900 5900 3600
Wire Wire Line
	5900 3600 6200 3600
NoConn ~ 6200 3700
Text Notes 5350 2700 0    60   ~ 0
Instead of connecting SLP to D11,\nit can also be connected to VMM via\na resistor of 20kOhms to 75kOhms.
NoConn ~ 6200 3100
Wire Wire Line
	7200 3400 7200 3300
Wire Wire Line
	7200 3500 7300 3500
Wire Wire Line
	7300 3500 7300 3200
Connection ~ 7300 3200
Wire Wire Line
	7200 3350 7400 3350
Wire Wire Line
	7400 3350 7400 3700
Connection ~ 7200 3350
Wire Wire Line
	4600 4900 4700 4900
NoConn ~ 7200 3600
NoConn ~ 7200 3700
Wire Wire Line
	7050 4900 7050 4400
Wire Wire Line
	6400 4750 6400 4900
Connection ~ 6400 4900
Wire Wire Line
	7300 3100 7200 3100
Wire Wire Line
	7300 2800 7300 3100
NoConn ~ 6200 3000
Wire Wire Line
	7200 2900 7200 3000
Wire Wire Line
	4100 2800 7300 2800
Wire Wire Line
	4300 5100 4300 2900
Wire Wire Line
	4400 5200 4400 2800
Connection ~ 4300 2900
Connection ~ 4400 2800
$Comp
L QTR-1A U3
U 1 1 5AD0F287
P 3700 3900
F 0 "U3" H 3700 3800 60  0000 C CNN
F 1 "QTR-1A" H 3700 3900 60  0000 C CNN
F 2 "" H 3700 3900 60  0001 C CNN
F 3 "" H 3700 3900 60  0001 C CNN
	1    3700 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	4100 4100 4600 4100
Wire Wire Line
	4100 4200 4700 4200
Wire Wire Line
	4100 4000 4300 4000
Connection ~ 4300 4000
$Comp
L R R3
U 1 1 5AEDD912
P 5100 3600
F 0 "R3" V 5180 3600 50  0000 C CNN
F 1 "1K" V 5100 3600 50  0000 C CNN
F 2 "" V 5030 3600 50  0001 C CNN
F 3 "" H 5100 3600 50  0001 C CNN
	1    5100 3600
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5AEDF31C
P 5100 3400
F 0 "R2" V 5180 3400 50  0000 C CNN
F 1 "1K" V 5100 3400 50  0000 C CNN
F 2 "" V 5030 3400 50  0001 C CNN
F 3 "" H 5100 3400 50  0001 C CNN
	1    5100 3400
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5AEDF348
P 5100 3200
F 0 "R1" V 5180 3200 50  0000 C CNN
F 1 "1K" V 5100 3200 50  0000 C CNN
F 2 "" V 5030 3200 50  0001 C CNN
F 3 "" H 5100 3200 50  0001 C CNN
	1    5100 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	4600 3600 4950 3600
Connection ~ 4600 4100
Wire Wire Line
	4600 3400 4950 3400
Connection ~ 4600 3600
Wire Wire Line
	4600 3200 4950 3200
Connection ~ 4600 3400
Wire Wire Line
	5600 4300 5600 3600
Wire Wire Line
	5600 3600 5250 3600
Connection ~ 5600 4300
Wire Wire Line
	5700 4400 5700 3400
Wire Wire Line
	5700 3400 5250 3400
Connection ~ 5700 4400
Wire Wire Line
	5800 4500 5800 3200
Wire Wire Line
	5800 3200 5250 3200
Connection ~ 5800 4500
NoConn ~ 5500 4700
NoConn ~ 5500 4800
Wire Wire Line
	4600 3200 4600 4900
Wire Wire Line
	4100 2900 7200 2900
$Comp
L Motor_DC M?
U 1 1 5AEE08C3
P 7700 3400
F 0 "M?" H 7800 3500 50  0000 L CNN
F 1 "Motor_DC" H 7800 3200 50  0000 L TNN
F 2 "" H 7700 3310 50  0001 C CNN
F 3 "" H 7700 3310 50  0001 C CNN
	1    7700 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3200 7700 3200
Wire Wire Line
	7400 3700 7700 3700
$EndSCHEMATC
