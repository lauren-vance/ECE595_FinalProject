# ECE595 FinalProject

This program was created for the final project of ECE 59500: Intro to Embedded Systems at IUPUI. It is written in C for the NXP FRDM-K64F. The included libraries were found with mbed online IDE. The file "main.c" was written by me. 

The motivation for this project was to create something useful as the COVID-19 pandemic entered the summer season. Enter: The Motorized Touchless Cooler with RFID-Controlled Lid! The cooler is embedded with the FRDM-K64F, which allows for control of movement via Bluetooth-connected Android app and control of lid motion with an RFID reader. You can remain socially distant while sharing your icy treats and stay safe knowing that you have control over who has access to the contents.

![Finished Product](https://i.imgur.com/Yweqs4Kh.jpg)

## Getting Started

The equipment used for this project are as follows:
- NXP FRDM-K64F
- L298N Motor Driver for 2x 12V DC Motors
- HC-06 Bluetooth Module
- SG90 Servo Motor
- RC522 RFID Module (with 2 Keys)
- 5V External Battery (to power K64F)
- 3S 11.1V Lipo Battery (to power DC motors)
- Breadboard/wires
- Wood of various sizes to create the base on which the cooler sits and the wheels are mounted
- 2x 6" Wheels with Shaft Hub and 1x Swivel Caster
- And finally...a cooler

*Note: various mounting hardware was also used to create the wooden base and mount the wheels. A small drop-section can be created in the wooden base to store the electronics so the cooler merely just rests on the wooden base to be carried off wherever you'd like.

## Images

First, use the mobile app to drive the cooler to you. App Screenshot:

![App Screenshot](https://i.imgur.com/go66SR5l.png)

Next, unlock the lid with the RFID card and it will open automatically:

![Unlocking the Lid](https://i.imgur.com/1eGaI2Vm.jpg)

Finally...grab a drink! Scan RFID card again to close the lid

![Grabbing a Drink!](https://i.imgur.com/cHlqaFnm.jpg)

Hardware Inside:

![Hardware Inside](https://i.imgur.com/bsjQhc5m.jpg)
