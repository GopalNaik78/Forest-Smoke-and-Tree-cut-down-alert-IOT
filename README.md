# Forest-Smoke-and-Tree-cut-down-alert-IOT

The project develops an IoT system that detects forest fires and illegal logging activities. It uses sensors to detect smoke and changes in tree orientation, triggering alerts to users through a web interface, email, and mobile notifications. The system can prevent environmental damage and protect ecosystems by providing real-time updates on potential dangers.

First Setup blynk 
Refer https://docs.blynk.io/en/getting-started/template-quick-setup


Installation instructions using Arduino IDE Boards Manager
==========================================================
Stable release link: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Development release link: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32, 64 bit and ARM).

Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the Arduino website.
Start Arduino and open Preferences window.
Enter one of the release links above into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
Open Boards Manager from Tools > Board menu and install esp32 platform (and don't forget to select your ESP32 board from Tools > Board menu after installation).

ADD Library's 
* Wire.h
* WiFi.h
* WiFiClient.h

Quick Installing
To install, use the Arduino Library Manager and search for "mpu6050" and install the library.

Manual Installing
To install this library:

install it using the Arduino Library manager ("Sketch" -> "Include Library" -> "Manage Libraries..."), or
download a zipfile from github using the "Download ZIP" button and install it using the IDE ("Sketch" -> "Include Library" -> "Add .ZIP Library..."
clone this git repository into your sketchbook/libraries folder.
For more info, see https://www.arduino.cc/en/Guide/Libraries


![image](https://user-images.githubusercontent.com/127333901/224089846-1a6c5f5b-38ca-4f7d-8b7f-407cedf638f1.png)



