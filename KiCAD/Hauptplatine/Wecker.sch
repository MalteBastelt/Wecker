EESchema Schematic File Version 2
LIBS:power
LIBS:device
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
LIBS:Wecker-cache
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
L ATMEGA328P-P IC1
U 1 1 5627CFEE
P 8575 2500
F 0 "IC1" H 7825 3750 40  0000 L BNN
F 1 "ATMEGA328P-P" H 8975 1100 40  0000 L BNN
F 2 "" H 8575 2500 30  0000 C CIN
F 3 "" H 8575 2500 60  0000 C CNN
	1    8575 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5627D0F9
P 7075 3700
F 0 "#PWR01" H 7075 3450 50  0001 C CNN
F 1 "GND" H 7075 3550 50  0000 C CNN
F 2 "" H 7075 3700 60  0000 C CNN
F 3 "" H 7075 3700 60  0000 C CNN
	1    7075 3700
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR02
U 1 1 5627D148
P 7075 1350
F 0 "#PWR02" H 7075 1200 50  0001 C CNN
F 1 "VCC" H 7075 1490 50  0000 C CNN
F 2 "" H 7075 1350 60  0000 C CNN
F 3 "" H 7075 1350 60  0000 C CNN
	1    7075 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR03
U 1 1 5627D248
P 775 950
F 0 "#PWR03" H 775 800 50  0001 C CNN
F 1 "+5V" H 775 1090 50  0000 C CNN
F 2 "" H 775 950 60  0000 C CNN
F 3 "" H 775 950 60  0000 C CNN
	1    775  950 
	1    0    0    -1  
$EndComp
$Comp
L 7805 U1
U 1 1 5627D26A
P 1425 1000
F 0 "U1" H 1575 804 60  0000 C CNN
F 1 "7805" H 1425 1200 60  0000 C CNN
F 2 "" H 1425 1000 60  0001 C CNN
F 3 "" H 1425 1000 60  0000 C CNN
	1    1425 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 5627D2D0
P 1825 950
F 0 "#PWR04" H 1825 800 50  0001 C CNN
F 1 "VCC" H 1825 1100 50  0000 C CNN
F 2 "" H 1825 950 60  0000 C CNN
F 3 "" H 1825 950 60  0000 C CNN
	1    1825 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5627D2E8
P 1425 1400
F 0 "#PWR05" H 1425 1150 50  0001 C CNN
F 1 "GND" H 1425 1250 50  0000 C CNN
F 2 "" H 1425 1400 60  0000 C CNN
F 3 "" H 1425 1400 60  0000 C CNN
	1    1425 1400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5627D475
P 925 1100
F 0 "C1" H 950 1200 50  0000 L CNN
F 1 "0,47µ" H 950 1000 50  0000 L CNN
F 2 "" H 963 950 30  0001 C CNN
F 3 "" H 925 1100 60  0000 C CNN
	1    925  1100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 56310BD8
P 3125 7500
F 0 "P4" H 3125 7650 50  0000 C CNN
F 1 "CONN_TASTER" V 3225 7500 50  0000 C CNN
F 2 "" H 3125 7500 60  0001 C CNN
F 3 "" H 3125 7500 60  0000 C CNN
	1    3125 7500
	0    1    1    0   
$EndComp
$Comp
L CONN_01X05 P5
U 1 1 56310C7C
P 3925 7500
F 0 "P5" H 3925 7800 50  0000 C CNN
F 1 "CONN_DREHENCODER" V 4025 7500 50  0000 C CNN
F 2 "" H 3925 7500 60  0001 C CNN
F 3 "" H 3925 7500 60  0000 C CNN
	1    3925 7500
	0    1    1    0   
$EndComp
$Comp
L CONN_01X08 P6
U 1 1 56310CD3
P 5025 7550
F 0 "P6" H 5025 8000 50  0000 C CNN
F 1 "CONN_DISPLAY" V 5125 7550 50  0000 C CNN
F 2 "" H 5025 7550 60  0001 C CNN
F 3 "" H 5025 7550 60  0000 C CNN
	1    5025 7550
	0    1    1    0   
$EndComp
Text GLabel 3225 7050 1    60   Input ~ 0
T1.1
Text GLabel 4225 7100 1    60   Input ~ 0
DE-A
Text GLabel 4075 7100 1    60   Input ~ 0
DE-C
Text GLabel 3925 7100 1    60   Input ~ 0
DE-B
Text GLabel 3775 7100 1    60   Input ~ 0
DE-D
Text GLabel 3625 7100 1    60   Input ~ 0
DE-E
Text GLabel 5525 7050 1    60   Input ~ 0
DISP-SI
Text GLabel 5375 7050 1    60   Input ~ 0
DISP-SCL
Text GLabel 5225 7050 1    60   Input ~ 0
DISP-A0
Text GLabel 5075 7050 1    60   Input ~ 0
DISP-RST
Text GLabel 4925 7050 1    60   Input ~ 0
DISP-CS1B
Text GLabel 4775 7050 1    60   Input ~ 0
DISP-LED
Text GLabel 4625 7050 1    60   Input ~ 0
DISP-GND
Text GLabel 4475 7050 1    60   Input ~ 0
DISP-VCC
Text GLabel 10075 2150 2    60   Input ~ 0
DISP-SI
Text GLabel 10075 2300 2    60   Input ~ 0
DISP-SCL
Text GLabel 10075 2450 2    60   Input ~ 0
DISP-A0
Text GLabel 10075 2900 2    60   Input ~ 0
DISP-LED
Text GLabel 10075 2750 2    60   Input ~ 0
DISP-CS1B
Text GLabel 10075 2600 2    60   Input ~ 0
DISP-RST
Text GLabel 10075 1350 2    60   Input ~ 0
T1.1
$Comp
L C C3
U 1 1 5631636A
P 9725 900
F 0 "C3" H 9750 1000 50  0000 L CNN
F 1 "100n" H 9750 800 50  0000 L CNN
F 2 "" H 9763 750 30  0001 C CNN
F 3 "" H 9725 900 60  0000 C CNN
	1    9725 900 
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 563164A4
P 9375 900
F 0 "R1" V 9455 900 50  0000 C CNN
F 1 "R" V 9375 900 50  0000 C CNN
F 2 "" V 9305 900 30  0001 C CNN
F 3 "" H 9375 900 30  0000 C CNN
	1    9375 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5631658B
P 9725 750
F 0 "#PWR06" H 9725 500 50  0001 C CNN
F 1 "GND" H 9725 600 50  0000 C CNN
F 2 "" H 9725 750 60  0000 C CNN
F 3 "" H 9725 750 60  0000 C CNN
	1    9725 750 
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR07
U 1 1 5631662A
P 3075 7300
F 0 "#PWR07" H 3075 7150 50  0001 C CNN
F 1 "VCC" H 3075 7450 50  0000 C CNN
F 2 "" H 3075 7300 60  0000 C CNN
F 3 "" H 3075 7300 60  0000 C CNN
	1    3075 7300
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 56316D79
P 10675 3850
F 0 "C5" H 10700 3950 50  0000 L CNN
F 1 "100n" H 10700 3750 50  0000 L CNN
F 2 "" H 10713 3700 30  0001 C CNN
F 3 "" H 10675 3850 60  0000 C CNN
	1    10675 3850
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 56316D82
P 11025 3850
F 0 "R4" V 11105 3850 50  0000 C CNN
F 1 "R" V 11025 3850 50  0000 C CNN
F 2 "" V 10955 3850 30  0001 C CNN
F 3 "" H 11025 3850 30  0000 C CNN
	1    11025 3850
	-1   0    0    1   
$EndComp
$Comp
L C C6
U 1 1 56316E48
P 10525 900
F 0 "C6" H 10550 1000 50  0000 L CNN
F 1 "100n" H 10550 800 50  0000 L CNN
F 2 "" H 10563 750 30  0001 C CNN
F 3 "" H 10525 900 60  0000 C CNN
	1    10525 900 
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 56316E51
P 10175 900
F 0 "R2" V 10255 900 50  0000 C CNN
F 1 "R" V 10175 900 50  0000 C CNN
F 2 "" V 10105 900 30  0001 C CNN
F 3 "" H 10175 900 30  0000 C CNN
	1    10175 900 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 56316E58
P 10525 750
F 0 "#PWR08" H 10525 500 50  0001 C CNN
F 1 "GND" H 10525 600 50  0000 C CNN
F 2 "" H 10525 750 60  0000 C CNN
F 3 "" H 10525 750 60  0000 C CNN
	1    10525 750 
	-1   0    0    1   
$EndComp
Text GLabel 10675 3500 2    60   Input ~ 0
DE-A
Text GLabel 10175 3600 2    60   Input ~ 0
DE-B
Text GLabel 10525 1450 2    60   Input ~ 0
DE-D
$Comp
L CP C2
U 1 1 56317C2F
P 1825 1100
F 0 "C2" H 1850 1200 50  0000 L CNN
F 1 "33µ" H 1850 1000 50  0000 L CNN
F 2 "" H 1863 950 30  0001 C CNN
F 3 "" H 1825 1100 60  0000 C CNN
	1    1825 1100
	1    0    0    -1  
$EndComp
Text GLabel 3250 3200 2    60   Input ~ 0
MP3-L
Text GLabel 3250 3600 2    60   Input ~ 0
MP3-R
Text GLabel 2475 2650 1    60   Input ~ 0
SPK-L+
Text GLabel 2625 2650 1    60   Input ~ 0
SPK-L-
$Comp
L TDA7266 U2
U 1 1 56312CE0
P 2225 3400
F 0 "U2" H 2675 3250 40  0000 C CNN
F 1 "TDA7266" H 2675 3200 40  0000 C CNN
F 2 "" H 1875 3400 30  0000 C CIN
F 3 "" H 2225 3400 60  0000 C CNN
	1    2225 3400
	-1   0    0    1   
$EndComp
Text GLabel 2575 4225 3    60   Input ~ 0
SPK-R+
Text GLabel 2425 4225 3    60   Input ~ 0
SPK-R-
$Comp
L GND #PWR09
U 1 1 5633D8CB
P 1975 3650
F 0 "#PWR09" H 1975 3400 50  0001 C CNN
F 1 "GND" H 1975 3500 50  0000 C CNN
F 2 "" H 1975 3650 60  0000 C CNN
F 3 "" H 1975 3650 60  0000 C CNN
	1    1975 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5633D9D5
P 2125 3700
F 0 "#PWR010" H 2125 3450 50  0001 C CNN
F 1 "GND" H 2125 3550 50  0000 C CNN
F 2 "" H 2125 3700 60  0000 C CNN
F 3 "" H 2125 3700 60  0000 C CNN
	1    2125 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P7
U 1 1 5634E192
P 5900 7525
F 0 "P7" H 5900 7675 50  0000 C CNN
F 1 "CONN_01X02" V 6000 7525 50  0000 C CNN
F 2 "" H 5900 7525 60  0001 C CNN
F 3 "" H 5900 7525 60  0000 C CNN
	1    5900 7525
	0    1    1    0   
$EndComp
Text GLabel 5800 7175 1    60   Input ~ 0
SPK-R-
Text GLabel 6000 7175 1    60   Input ~ 0
SPK-R+
$Comp
L CONN_01X02 P8
U 1 1 5634E1FB
P 6550 7525
F 0 "P8" H 6550 7675 50  0000 C CNN
F 1 "CONN_01X02" V 6650 7525 50  0000 C CNN
F 2 "" H 6550 7525 60  0001 C CNN
F 3 "" H 6550 7525 60  0000 C CNN
	1    6550 7525
	0    1    1    0   
$EndComp
Text GLabel 6450 7175 1    60   Input ~ 0
SPK-L-
Text GLabel 6650 7175 1    60   Input ~ 0
SPK-L+
$Comp
L R R5
U 1 1 5634F30F
P 1450 2600
F 0 "R5" V 1530 2600 50  0000 C CNN
F 1 "10k" V 1450 2600 50  0000 C CNN
F 2 "" V 1380 2600 30  0001 C CNN
F 3 "" H 1450 2600 30  0000 C CNN
	1    1450 2600
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5634F3A8
P 1450 2775
F 0 "R6" V 1530 2775 50  0000 C CNN
F 1 "10k" V 1450 2775 50  0000 C CNN
F 2 "" V 1380 2775 30  0001 C CNN
F 3 "" H 1450 2775 30  0000 C CNN
	1    1450 2775
	0    1    1    0   
$EndComp
$Comp
L CP C7
U 1 1 5634F502
P 1600 2325
F 0 "C7" H 1625 2425 50  0000 L CNN
F 1 "220nF" H 1625 2225 50  0000 L CNN
F 2 "" H 1638 2175 30  0001 C CNN
F 3 "" H 1600 2325 60  0000 C CNN
	1    1600 2325
	-1   0    0    1   
$EndComp
$Comp
L CP C8
U 1 1 5634F589
P 1600 3050
F 0 "C8" H 1625 3150 50  0000 L CNN
F 1 "220nF" H 1625 2950 50  0000 L CNN
F 2 "" H 1638 2900 30  0001 C CNN
F 3 "" H 1600 3050 60  0000 C CNN
	1    1600 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5634F9A3
P 1600 2175
F 0 "#PWR011" H 1600 1925 50  0001 C CNN
F 1 "GND" H 1600 2025 50  0000 C CNN
F 2 "" H 1600 2175 60  0000 C CNN
F 3 "" H 1600 2175 60  0000 C CNN
	1    1600 2175
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR012
U 1 1 5634FB7C
P 1600 3200
F 0 "#PWR012" H 1600 2950 50  0001 C CNN
F 1 "GND" H 1600 3050 50  0000 C CNN
F 2 "" H 1600 3200 60  0000 C CNN
F 3 "" H 1600 3200 60  0000 C CNN
	1    1600 3200
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 56350304
P 3100 3200
F 0 "C11" H 3125 3300 50  0000 L CNN
F 1 "0,22u" H 3125 3100 50  0000 L CNN
F 2 "" H 3138 3050 30  0001 C CNN
F 3 "" H 3100 3200 60  0000 C CNN
	1    3100 3200
	0    1    1    0   
$EndComp
$Comp
L C C12
U 1 1 56350442
P 3100 3600
F 0 "C12" H 3125 3700 50  0000 L CNN
F 1 "0,22u" H 3125 3500 50  0000 L CNN
F 2 "" H 3138 3450 30  0001 C CNN
F 3 "" H 3100 3600 60  0000 C CNN
	1    3100 3600
	0    1    1    0   
$EndComp
$Comp
L C C9
U 1 1 56350E11
P 1750 4375
F 0 "C9" H 1775 4475 50  0000 L CNN
F 1 "100nF" H 1775 4275 50  0000 L CNN
F 2 "" H 1788 4225 30  0001 C CNN
F 3 "" H 1750 4375 60  0000 C CNN
	1    1750 4375
	1    0    0    -1  
$EndComp
$Comp
L CP C10
U 1 1 56350E90
P 2025 4375
F 0 "C10" H 2050 4475 50  0000 L CNN
F 1 "470uF" H 2050 4275 50  0000 L CNN
F 2 "" H 2063 4225 30  0001 C CNN
F 3 "" H 2025 4375 60  0000 C CNN
	1    2025 4375
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P2
U 1 1 563A4E2C
P 1875 7525
F 0 "P2" H 1875 7975 50  0000 C CNN
F 1 "CONN_MP3Player" V 1975 7525 50  0000 C CNN
F 2 "" H 1875 7525 60  0001 C CNN
F 3 "" H 1875 7525 60  0000 C CNN
	1    1875 7525
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 P9
U 1 1 563A56CF
P 10275 1900
F 0 "P9" H 10275 2050 50  0000 C CNN
F 1 "CONN_OSC" V 10375 1900 50  0000 C CNN
F 2 "" H 10275 1900 60  0001 C CNN
F 3 "" H 10275 1900 60  0000 C CNN
	1    10275 1900
	1    0    0    -1  
$EndComp
Text GLabel 1050 6925 1    60   Input ~ 0
MP3-L
Text GLabel 900  6925 1    60   Input ~ 0
MP3-R
$Comp
L GND #PWR013
U 1 1 563A5EC8
P 1525 7325
F 0 "#PWR013" H 1525 7075 50  0001 C CNN
F 1 "GND" H 1525 7175 50  0000 C CNN
F 2 "" H 1525 7325 60  0000 C CNN
F 3 "" H 1525 7325 60  0000 C CNN
	1    1525 7325
	-1   0    0    1   
$EndComp
Text GLabel 1925 7050 1    60   Input ~ 0
MP3_T1
Text GLabel 2050 7050 1    60   Input ~ 0
MP3_T3
$Comp
L C C4
U 1 1 56547168
P 9825 3850
F 0 "C4" H 9850 3950 50  0000 L CNN
F 1 "100n" H 9850 3750 50  0000 L CNN
F 2 "" H 9863 3700 30  0001 C CNN
F 3 "" H 9825 3850 60  0000 C CNN
	1    9825 3850
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 56547170
P 10175 3850
F 0 "R3" V 10255 3850 50  0000 C CNN
F 1 "R" V 10175 3850 50  0000 C CNN
F 2 "" V 10105 3850 30  0001 C CNN
F 3 "" H 10175 3850 30  0000 C CNN
	1    10175 3850
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR014
U 1 1 56549443
P 9825 4000
F 0 "#PWR014" H 9825 3850 50  0001 C CNN
F 1 "VCC" H 9825 4140 50  0000 C CNN
F 2 "" H 9825 4000 60  0000 C CNN
F 3 "" H 9825 4000 60  0000 C CNN
	1    9825 4000
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR015
U 1 1 5654992D
P 10675 4000
F 0 "#PWR015" H 10675 3850 50  0001 C CNN
F 1 "VCC" H 10675 4140 50  0000 C CNN
F 2 "" H 10675 4000 60  0000 C CNN
F 3 "" H 10675 4000 60  0000 C CNN
	1    10675 4000
	-1   0    0    1   
$EndComp
Text GLabel 4075 6575 1    60   Input ~ 0
DE-C
Text GLabel 3625 6575 1    60   Input ~ 0
DE-E
$Comp
L VCC #PWR016
U 1 1 5654E6BC
P 3625 6575
F 0 "#PWR016" H 3625 6425 50  0001 C CNN
F 1 "VCC" H 3625 6715 50  0000 C CNN
F 2 "" H 3625 6575 60  0000 C CNN
F 3 "" H 3625 6575 60  0000 C CNN
	1    3625 6575
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR017
U 1 1 5654E7DF
P 4075 6575
F 0 "#PWR017" H 4075 6325 50  0001 C CNN
F 1 "GND" H 4075 6425 50  0000 C CNN
F 2 "" H 4075 6575 60  0000 C CNN
F 3 "" H 4075 6575 60  0000 C CNN
	1    4075 6575
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 565587D9
P 5700 5375
F 0 "P3" H 5700 5525 50  0000 C CNN
F 1 "LED_Bilder" V 5800 5375 50  0000 C CNN
F 2 "" H 5700 5375 60  0001 C CNN
F 3 "" H 5700 5375 60  0000 C CNN
	1    5700 5375
	0    1    1    0   
$EndComp
Text GLabel 1800 7050 1    60   Input ~ 0
MP3_T4
Text GLabel 1675 7050 1    60   Input ~ 0
MP3_T5
Text GLabel 2300 7050 1    60   Input ~ 0
MP3_ON1
Text GLabel 2175 7050 1    60   Input ~ 0
MP3_ON2
Text GLabel 10075 3425 2    60   Input ~ 0
MP3-T5
Text GLabel 10075 3300 2    60   Input ~ 0
MP3-T4
Text GLabel 10075 3175 2    60   Input ~ 0
MP3-T1
Text GLabel 10075 3050 2    60   Input ~ 0
MP3-T3
Text GLabel 10650 2975 2    60   Input ~ 0
MP3_ON1
Text GLabel 10675 2825 2    60   Input ~ 0
MP3_ON2
Text GLabel 9575 4400 2    60   Input ~ 0
Amp-Mute
Text GLabel 8800 975  0    60   Input ~ 0
Amp-Power
Text GLabel 10475 1650 2    60   Input ~ 0
LED-Bilder
Text GLabel 1050 2600 0    60   Input ~ 0
Amp-Mute
Text GLabel 1075 2775 0    60   Input ~ 0
Amp-Power
Text GLabel 9775 5675 0    60   Input ~ 0
LED-Bilder
Text GLabel 9775 5675 2    60   Input ~ 0
Transistorschaltung
$Comp
L GND #PWR018
U 1 1 5657D772
P 5750 5175
F 0 "#PWR018" H 5750 4925 50  0001 C CNN
F 1 "GND" H 5750 5025 50  0000 C CNN
F 2 "" H 5750 5175 60  0000 C CNN
F 3 "" H 5750 5175 60  0000 C CNN
	1    5750 5175
	-1   0    0    1   
$EndComp
Text GLabel 5650 4900 1    60   Input ~ 0
Transistor-Emitter
$Comp
L GND #PWR019
U 1 1 5657DFBD
P 2025 4525
F 0 "#PWR019" H 2025 4275 50  0001 C CNN
F 1 "GND" H 2025 4375 50  0000 C CNN
F 2 "" H 2025 4525 60  0000 C CNN
F 3 "" H 2025 4525 60  0000 C CNN
	1    2025 4525
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5657E022
P 1750 4525
F 0 "#PWR020" H 1750 4275 50  0001 C CNN
F 1 "GND" H 1750 4375 50  0000 C CNN
F 2 "" H 1750 4525 60  0000 C CNN
F 3 "" H 1750 4525 60  0000 C CNN
	1    1750 4525
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR021
U 1 1 5657E6F9
P 2325 2525
F 0 "#PWR021" H 2325 2375 50  0001 C CNN
F 1 "VCC" H 2325 2665 50  0000 C CNN
F 2 "" H 2325 2525 60  0000 C CNN
F 3 "" H 2325 2525 60  0000 C CNN
	1    2325 2525
	1    0    0    -1  
$EndComp
Text GLabel 1550 7050 1    60   Input ~ 0
MP3_VCC
$Comp
L VCC #PWR022
U 1 1 565765D3
P 1750 4025
F 0 "#PWR022" H 1750 3875 50  0001 C CNN
F 1 "VCC" H 1750 4165 50  0000 C CNN
F 2 "" H 1750 4025 60  0000 C CNN
F 3 "" H 1750 4025 60  0000 C CNN
	1    1750 4025
	1    0    0    -1  
$EndComp
Text Notes 1050 700  0    60   ~ 0
Spannungsregler 3,3V
Text Notes 2150 2100 0    60   ~ 0
Audio-Verstärker
$Comp
L LM317T U3
U 1 1 56577675
P 1225 5625
F 0 "U3" H 1025 5825 40  0000 C CNN
F 1 "LM317T" H 1225 5825 40  0000 L CNN
F 2 "" H 1225 5725 30  0000 C CIN
F 3 "" H 1225 5625 60  0000 C CNN
	1    1225 5625
	1    0    0    -1  
$EndComp
Text Notes 775  5300 0    60   ~ 0
Spannungsregler 1,5V
$Comp
L VCC #PWR023
U 1 1 56577A6D
P 825 5575
F 0 "#PWR023" H 825 5425 50  0001 C CNN
F 1 "VCC" H 825 5725 50  0000 C CNN
F 2 "" H 825 5575 60  0000 C CNN
F 3 "" H 825 5575 60  0000 C CNN
	1    825  5575
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 56577AD5
P 1700 5725
F 0 "R7" V 1780 5725 50  0000 C CNN
F 1 "10k" V 1700 5725 50  0000 C CNN
F 2 "" V 1630 5725 30  0001 C CNN
F 3 "" H 1700 5725 30  0000 C CNN
	1    1700 5725
	-1   0    0    1   
$EndComp
$Comp
L R R8
U 1 1 56577B87
P 1700 6025
F 0 "R8" V 1780 6025 50  0000 C CNN
F 1 "220" V 1700 6025 50  0000 C CNN
F 2 "" V 1630 6025 30  0001 C CNN
F 3 "" H 1700 6025 30  0000 C CNN
	1    1700 6025
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR024
U 1 1 56578070
P 1700 6175
F 0 "#PWR024" H 1700 5925 50  0001 C CNN
F 1 "GND" H 1700 6025 50  0000 C CNN
F 2 "" H 1700 6175 60  0000 C CNN
F 3 "" H 1700 6175 60  0000 C CNN
	1    1700 6175
	1    0    0    -1  
$EndComp
Text GLabel 1875 5575 2    60   Input ~ 0
MP3_VCC
Text Notes 2625 1100 0    60   ~ 0
Connector Spannungsversorgung
Wire Wire Line
	7675 3700 7075 3700
Wire Wire Line
	7675 3600 7675 3700
Wire Wire Line
	7675 1400 7075 1400
Wire Wire Line
	7075 1350 7075 2000
Wire Wire Line
	7075 2000 7675 2000
Connection ~ 7075 1400
Wire Wire Line
	7675 1700 7075 1700
Connection ~ 7075 1700
Wire Wire Line
	775  950  1025 950 
Wire Wire Line
	1425 1400 1425 1250
Wire Wire Line
	925  1250 1825 1250
Connection ~ 1425 1250
Wire Wire Line
	3175 7300 3175 7150
Wire Wire Line
	3175 7150 3225 7150
Wire Wire Line
	3225 7150 3225 7050
Connection ~ 3225 7050
Connection ~ 3175 7300
Wire Wire Line
	3625 7100 3625 7200
Wire Wire Line
	3625 7200 3725 7200
Wire Wire Line
	3725 7200 3725 7300
Wire Wire Line
	3775 7100 3775 7200
Wire Wire Line
	3775 7200 3825 7200
Wire Wire Line
	3825 7200 3825 7300
Wire Wire Line
	3925 7100 3925 7300
Wire Wire Line
	4025 7300 4025 7200
Wire Wire Line
	4025 7200 4075 7200
Wire Wire Line
	4075 7200 4075 7100
Wire Wire Line
	4125 7300 4125 7200
Wire Wire Line
	4125 7200 4225 7200
Wire Wire Line
	4225 7200 4225 7100
Connection ~ 4225 7100
Connection ~ 4075 7100
Connection ~ 3925 7100
Connection ~ 3775 7100
Connection ~ 3625 7100
Connection ~ 3725 7300
Connection ~ 3825 7300
Connection ~ 3925 7300
Connection ~ 4025 7300
Connection ~ 4125 7300
Connection ~ 4675 7350
Connection ~ 4775 7350
Connection ~ 4875 7350
Connection ~ 4975 7350
Connection ~ 5075 7350
Connection ~ 5175 7350
Connection ~ 5275 7350
Connection ~ 5375 7350
Wire Wire Line
	5375 7350 5525 7350
Wire Wire Line
	5525 7350 5525 7050
Wire Wire Line
	5375 7050 5375 7250
Wire Wire Line
	5375 7250 5275 7250
Wire Wire Line
	5275 7250 5275 7350
Wire Wire Line
	5175 7350 5175 7200
Wire Wire Line
	5175 7200 5225 7200
Wire Wire Line
	5225 7200 5225 7050
Wire Wire Line
	5075 7050 5075 7350
Wire Wire Line
	4975 7350 4975 7200
Wire Wire Line
	4975 7200 4925 7200
Wire Wire Line
	4925 7200 4925 7050
Wire Wire Line
	4775 7050 4775 7250
Wire Wire Line
	4775 7250 4875 7250
Wire Wire Line
	4875 7250 4875 7350
Wire Wire Line
	4775 7350 4775 7300
Wire Wire Line
	4775 7300 4625 7300
Wire Wire Line
	4625 7300 4625 7050
Wire Wire Line
	4675 7350 4475 7350
Wire Wire Line
	4475 7350 4475 7050
Connection ~ 9575 2100
Connection ~ 9575 2000
Wire Wire Line
	9575 2250 9725 2250
Wire Wire Line
	9725 2250 9725 2150
Wire Wire Line
	9725 2150 10075 2150
Wire Wire Line
	9575 2350 9825 2350
Wire Wire Line
	9825 2350 9825 2300
Wire Wire Line
	9825 2300 10075 2300
Wire Wire Line
	9575 2450 10075 2450
Wire Wire Line
	9575 2550 9825 2550
Wire Wire Line
	9825 2550 9825 2600
Wire Wire Line
	9825 2600 10075 2600
Wire Wire Line
	9575 2650 9725 2650
Wire Wire Line
	9725 2650 9725 2750
Wire Wire Line
	9725 2750 10075 2750
Wire Wire Line
	9575 2750 9675 2750
Wire Wire Line
	9675 2750 9675 2900
Wire Wire Line
	9675 2900 10075 2900
Connection ~ 10075 2900
Connection ~ 10075 2750
Connection ~ 10075 2600
Connection ~ 10075 2450
Connection ~ 10075 2300
Connection ~ 10075 2150
Connection ~ 9575 2250
Connection ~ 9575 2350
Connection ~ 9575 2450
Connection ~ 9575 2550
Connection ~ 9575 2650
Connection ~ 9575 2750
Wire Wire Line
	10025 1950 10025 2100
Wire Wire Line
	10025 2100 9575 2100
Wire Wire Line
	10075 1850 9925 1850
Wire Wire Line
	9925 1850 9925 2000
Wire Wire Line
	9925 2000 9575 2000
Wire Wire Line
	9725 1500 9575 1500
Wire Wire Line
	9725 1350 10075 1350
Wire Wire Line
	9725 1150 9375 1150
Wire Wire Line
	9375 1150 9375 1050
Connection ~ 9725 1150
Wire Wire Line
	9375 750  9725 750 
Connection ~ 9725 750 
Connection ~ 9375 750 
Connection ~ 9725 1050
Connection ~ 3075 7300
Connection ~ 9725 1350
Connection ~ 10075 1350
Connection ~ 9575 1500
Connection ~ 9575 1600
Wire Wire Line
	9575 1600 9875 1600
Wire Wire Line
	9875 1600 9875 1450
Wire Wire Line
	9875 1450 10525 1450
Connection ~ 9575 1700
Connection ~ 9575 1800
Wire Wire Line
	11025 3600 11025 3700
Connection ~ 10675 3600
Wire Wire Line
	11025 4000 10675 4000
Connection ~ 10675 4000
Connection ~ 11025 4000
Connection ~ 10675 3700
Wire Wire Line
	10525 1150 10175 1150
Wire Wire Line
	10175 1150 10175 1050
Connection ~ 10525 1150
Wire Wire Line
	10175 750  10525 750 
Connection ~ 10525 750 
Connection ~ 10175 750 
Connection ~ 10525 1050
Connection ~ 10525 1450
Connection ~ 2625 2650
Connection ~ 2475 2650
Connection ~ 2950 3200
Connection ~ 2950 3600
Connection ~ 2875 3600
Connection ~ 2875 3200
Wire Wire Line
	2575 2950 2575 2800
Wire Wire Line
	2575 2800 2625 2800
Wire Wire Line
	2625 2800 2625 2650
Wire Wire Line
	2475 2650 2475 3000
Connection ~ 2475 3000
Connection ~ 2575 2950
Connection ~ 2425 4225
Connection ~ 2575 4225
Wire Wire Line
	2425 3800 2425 4225
Wire Wire Line
	2575 3875 2575 4225
Connection ~ 2575 3875
Connection ~ 2425 3800
Connection ~ 2275 3750
Connection ~ 2125 3700
Connection ~ 1975 3650
Connection ~ 2075 3100
Connection ~ 2225 3050
Connection ~ 2325 3050
Wire Wire Line
	5850 7325 5850 7275
Wire Wire Line
	5850 7275 5800 7275
Wire Wire Line
	5800 7275 5800 7175
Wire Wire Line
	5950 7325 5950 7275
Wire Wire Line
	5950 7275 6000 7275
Wire Wire Line
	6000 7275 6000 7175
Wire Wire Line
	6500 7325 6500 7275
Wire Wire Line
	6500 7275 6450 7275
Wire Wire Line
	6450 7275 6450 7175
Wire Wire Line
	6600 7325 6600 7275
Wire Wire Line
	6600 7275 6650 7275
Wire Wire Line
	6650 7275 6650 7175
Connection ~ 1600 2600
Connection ~ 1600 2775
Wire Wire Line
	1600 2600 1600 2475
Wire Wire Line
	1600 2775 1600 2900
Connection ~ 1600 2475
Connection ~ 1600 2900
Connection ~ 1600 2200
Connection ~ 1600 3200
Connection ~ 1600 3175
Wire Wire Line
	1600 2775 2075 2775
Wire Wire Line
	2075 2775 2075 3100
Wire Wire Line
	1600 2600 2225 2600
Wire Wire Line
	2225 2600 2225 3050
Connection ~ 3250 3200
Connection ~ 3250 3600
Connection ~ 1750 4225
Wire Wire Line
	10025 1950 10075 1950
Connection ~ 10075 1950
Connection ~ 10075 1850
Connection ~ 9825 3600
Wire Wire Line
	10175 4000 9825 4000
Connection ~ 9825 4000
Connection ~ 9825 3700
Wire Wire Line
	10175 3600 10175 3700
Connection ~ 11025 3700
Connection ~ 10175 3700
Connection ~ 1525 7325
Connection ~ 1625 7325
Connection ~ 1725 7325
Connection ~ 1825 7325
Connection ~ 1925 7325
Connection ~ 2025 7325
Connection ~ 2125 7325
Connection ~ 2225 7325
Connection ~ 10175 3600
Wire Wire Line
	10075 3050 9825 3050
Wire Wire Line
	9575 3175 10075 3175
Wire Wire Line
	9575 3300 10075 3300
Wire Wire Line
	9825 3050 9825 3100
Wire Wire Line
	9825 3100 9575 3100
Wire Wire Line
	9575 3175 9575 3200
Wire Wire Line
	10075 3425 9575 3425
Wire Wire Line
	9575 3425 9575 3400
Wire Wire Line
	9575 3000 9575 2975
Wire Wire Line
	9575 2975 10650 2975
Wire Wire Line
	9575 2850 9625 2850
Wire Wire Line
	9625 2850 9625 2825
Wire Wire Line
	9625 2825 10675 2825
Connection ~ 2025 4225
Wire Wire Line
	10525 1450 10525 1050
Wire Wire Line
	9725 1050 9725 1500
Wire Wire Line
	9575 3600 10175 3600
Wire Wire Line
	9575 3500 10675 3500
Wire Wire Line
	10675 3500 10675 3700
Wire Wire Line
	11025 3600 10675 3600
Wire Wire Line
	9825 3700 9825 3600
Wire Wire Line
	9575 3700 9575 4400
Wire Wire Line
	9575 1400 9575 1225
Wire Wire Line
	9575 1225 8975 1225
Wire Wire Line
	8975 1225 8975 975 
Wire Wire Line
	8975 975  8800 975 
Wire Wire Line
	9575 1700 9925 1700
Wire Wire Line
	9925 1700 9925 1650
Wire Wire Line
	9925 1650 10475 1650
Wire Wire Line
	1050 2600 1300 2600
Wire Wire Line
	1075 2775 1300 2775
Wire Wire Line
	5650 5175 5650 4900
Wire Wire Line
	1625 7325 1625 7125
Wire Wire Line
	1625 7125 1550 7125
Wire Wire Line
	1550 7125 1550 7050
Wire Wire Line
	1725 7325 1725 7125
Wire Wire Line
	1725 7125 1675 7125
Wire Wire Line
	1675 7125 1675 7050
Wire Wire Line
	1825 7325 1825 7125
Wire Wire Line
	1825 7125 1800 7125
Wire Wire Line
	1800 7125 1800 7050
Wire Wire Line
	1925 7325 1925 7050
Wire Wire Line
	2025 7125 2050 7125
Wire Wire Line
	2050 7125 2050 7050
Wire Wire Line
	2025 7325 2025 7125
Wire Wire Line
	2125 7325 2125 7125
Wire Wire Line
	2125 7125 2175 7125
Wire Wire Line
	2175 7125 2175 7050
Wire Wire Line
	2225 7325 2225 7125
Wire Wire Line
	2225 7125 2300 7125
Wire Wire Line
	2300 7125 2300 7050
Wire Wire Line
	2875 3200 2950 3200
Wire Wire Line
	2950 3600 2875 3600
Wire Wire Line
	2325 3050 2325 2525
Wire Wire Line
	2275 4025 2275 3750
Wire Wire Line
	1750 4025 2275 4025
Wire Wire Line
	2025 4025 2025 4225
Wire Wire Line
	1750 4025 1750 4225
Connection ~ 2025 4025
Wire Wire Line
	1625 5575 1875 5575
Connection ~ 1700 5875
Wire Wire Line
	1225 5875 1700 5875
Connection ~ 1700 5575
Wire Wire Line
	800  7125 900  7125
Wire Wire Line
	900  7125 900  6925
Wire Wire Line
	1300 7125 1300 6925
Wire Wire Line
	1300 6925 1050 6925
Wire Wire Line
	1100 7125 950  7125
Wire Wire Line
	950  7125 950  7625
Wire Wire Line
	500  7525 1300 7525
Connection ~ 1100 7525
Connection ~ 950  7525
Connection ~ 800  7525
$Comp
L GND #PWR025
U 1 1 565876AB
P 950 7625
F 0 "#PWR025" H 950 7375 50  0001 C CNN
F 1 "GND" H 950 7475 50  0000 C CNN
F 2 "" H 950 7625 60  0000 C CNN
F 3 "" H 950 7625 60  0000 C CNN
	1    950  7625
	1    0    0    -1  
$EndComp
Wire Wire Line
	600  7125 500  7125
Wire Wire Line
	500  7125 500  7525
Connection ~ 600  7525
$Comp
L CBP U5
U 1 1 5658541B
P 1300 7325
F 0 "U5" H 1300 7575 60  0000 C CNN
F 1 "CBP" H 1300 7275 60  0000 C CNN
F 2 "" H 1300 7325 60  0001 C CNN
F 3 "" H 1300 7325 60  0000 C CNN
	1    1300 7325
	0    -1   -1   0   
$EndComp
$Comp
L CBP U4
U 1 1 565855EE
P 800 7325
F 0 "U4" H 800 7575 60  0000 C CNN
F 1 "CBP" H 800 7275 60  0000 C CNN
F 2 "CBP:testneu" H 800 7325 60  0001 C CNN
F 3 "" H 800 7325 60  0000 C CNN
	1    800  7325
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
