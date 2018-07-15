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
LIBS:AFRM3-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
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
P 4100 3200
F 0 "#PWR1" H 4100 3050 50  0001 C CNN
F 1 "+6V" H 4100 3340 50  0000 C CNN
F 2 "" H 4100 3200 50  0001 C CNN
F 3 "" H 4100 3200 50  0001 C CNN
	1    4100 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5AA41E9A
P 4100 3300
F 0 "#PWR2" H 4100 3050 50  0001 C CNN
F 1 "GND" H 4100 3150 50  0000 C CNN
F 2 "" H 4100 3300 50  0001 C CNN
F 3 "" H 4100 3300 50  0001 C CNN
	1    4100 3300
	1    0    0    -1  
$EndComp
$Comp
L Audio-Jack-2 J1
U 1 1 5AA41F3B
P 6600 4650
F 0 "J1" H 6575 4725 50  0000 C CNN
F 1 "Audio-Jack-2" H 6575 4475 50  0000 C CNN
F 2 "" H 6850 4650 50  0001 C CNN
F 3 "" H 6850 4650 50  0001 C CNN
	1    6600 4650
	-1   0    0    -1  
$EndComp
Text Notes 6750 4350 0    60   ~ 0
Direction:\n1: Up (I)\n2: None (O)\n4: Down (II)
Text Notes 7350 7500 0    60   ~ 0
AFRM3
Text Notes 10600 7650 0    60   ~ 0
0.5
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
22 Mar 2018
$Comp
L Motor_DC_Encoder M?
U 1 1 5AA55CC6
P 8150 1900
F 0 "M?" H 7900 1900 50  0000 L CNN
F 1 "Motor_DC_Encoder" H 7300 1850 50  0000 L TNN
F 2 "" H 8150 1810 50  0001 C CNN
F 3 "" H 8150 1810 50  0001 C CNN
	1    8150 1900
	-1   0    0    -1  
$EndComp
$Comp
L SW_SP3T SW2
U 1 1 5AA42113
P 6600 4400
F 0 "SW2" H 6600 4550 50  0000 C CNN
F 1 "SW_SP3T" H 7000 4400 50  0000 C CNN
F 2 "" H 5975 4575 50  0001 C CNN
F 3 "" H 5975 4575 50  0001 C CNN
	1    6600 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7300 3900 5500 3900
Wire Wire Line
	4300 5100 4700 5100
Wire Wire Line
	4100 3300 7000 3300
Wire Wire Line
	5500 1800 5500 3300
Connection ~ 5500 3300
Wire Wire Line
	5800 2200 7600 2200
Wire Wire Line
	5600 3400 5600 2100
Wire Wire Line
	5600 2100 7600 2100
Wire Wire Line
	5500 1800 7600 1800
Wire Wire Line
	5900 1700 7600 1700
Wire Wire Line
	4400 3200 4400 5200
Connection ~ 4300 3300
Wire Wire Line
	5500 4300 6400 4300
Wire Wire Line
	5500 4400 6000 4400
Wire Wire Line
	6000 4400 6000 4500
Wire Wire Line
	6000 4500 6400 4500
Wire Wire Line
	5900 4650 6400 4650
Wire Wire Line
	5900 4650 5900 4500
Wire Wire Line
	5900 4500 5500 4500
Wire Wire Line
	7600 2000 7500 2000
Wire Wire Line
	7500 2000 7500 5000
Wire Wire Line
	7600 1900 7400 1900
Wire Wire Line
	7400 1900 7400 4900
Wire Wire Line
	7400 4900 5800 4900
Wire Wire Line
	5800 4900 5800 4700
Wire Wire Line
	5800 4700 5500 4700
Wire Wire Line
	7500 5000 5700 5000
Wire Wire Line
	5700 5000 5700 4800
Wire Wire Line
	5700 4800 5500 4800
NoConn ~ 6400 4400
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
NoConn ~ 4700 4200
NoConn ~ 4700 4100
NoConn ~ 4700 4000
NoConn ~ 4700 3900
NoConn ~ 4700 3800
Wire Wire Line
	6200 4750 6400 4750
Wire Wire Line
	6850 4400 6800 4400
Connection ~ 6850 4400
NoConn ~ 5500 4200
Wire Wire Line
	4400 5200 4700 5200
Connection ~ 4400 3200
Wire Wire Line
	5500 4900 5600 4900
Wire Wire Line
	5600 4900 5600 5100
Wire Wire Line
	5600 5100 6850 5100
Wire Wire Line
	6850 5100 6850 4400
Wire Wire Line
	6200 4750 6200 5100
Connection ~ 6200 5100
Wire Wire Line
	4300 5100 4300 3300
$Comp
L TB6612FNG-Module U?
U 1 1 5ACD1357
P 6500 3350
F 0 "U?" H 6500 3250 60  0000 C CNN
F 1 "TB6612FNG-Module" H 6500 3350 60  0000 C CNN
F 2 "" H 6500 3350 60  0001 C CNN
F 3 "" H 6500 3350 60  0001 C CNN
	1    6500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 4900 4500 4900
Wire Wire Line
	4500 4900 4500 3400
Wire Wire Line
	4500 3400 5600 3400
Wire Wire Line
	4100 3200 5900 3200
Wire Wire Line
	7000 2900 7100 2900
Wire Wire Line
	7100 2700 7000 2700
Wire Wire Line
	7000 3000 7200 3000
Wire Wire Line
	7200 2600 7000 2600
Wire Wire Line
	7000 3100 7300 3100
Wire Wire Line
	7300 2500 7300 3900
Wire Wire Line
	7300 2500 7000 2500
Connection ~ 7300 3100
Connection ~ 7200 3000
Connection ~ 7100 2900
Wire Wire Line
	7100 4000 5500 4000
Wire Wire Line
	7100 2700 7100 4000
Wire Wire Line
	7200 4100 5500 4100
Wire Wire Line
	7200 2600 7200 4100
Wire Wire Line
	6000 3300 6000 3200
Wire Wire Line
	7000 3300 7000 3200
Connection ~ 6000 3300
Wire Wire Line
	6000 2900 6000 2800
Wire Wire Line
	5900 3000 6000 3000
Wire Wire Line
	5900 1700 5900 3000
Wire Wire Line
	5900 2700 6000 2700
Wire Wire Line
	6000 2850 5800 2850
Wire Wire Line
	5800 2850 5800 2200
Connection ~ 6000 2850
Connection ~ 5900 2700
Wire Wire Line
	6000 2600 5600 2600
Connection ~ 5600 2600
Wire Wire Line
	5900 3200 5900 3100
Wire Wire Line
	5900 3100 6000 3100
Wire Wire Line
	7000 2800 7000 2350
Wire Wire Line
	7000 2350 5600 2350
Connection ~ 5600 2350
$EndSCHEMATC
