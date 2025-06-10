# Sumobot Engineering Prototype
CHCI TEL4M Summative Design Project

# Usage Guide
This project is intended to be a template for other groups' projects. You are encouraged to modify this to your liking but it does work out of the box as a simple motion controller. Regardless of whether or not you want to modify the code, there are a few steps you need to do to make it runnable.

All of the final code is in `actual-code/main`.

1. If you are programming on Linux, you have to grant your USB port read and write permissions. First thing you need to do is check which port your ESP32 is connected to. This is done by executing `ls /dev` which shows all of your connected devices. You should see something like `ttyACM0`. Execute the command `sudo chmod 666 /dev/ttyACM0` or whatever port it shows to grant it the necessary permissions.
2. Next, you have to add yourself to the `dialout` group. To do this, execute `sudo usermod -a -G <username> dialout` and replace `<username>` with the name of your user on Linux.
3. This project depends on 2 libraries which are not built into the IDE. These libraries are "WebSockets" by Markus Sattler and "ArduinoJson" by Benoit.
4. You also need to install the drivers for each of the boards. In the Arduino IDE board manager, install "esp32" by Espressif Systems.
5. Before you compile and upload the code, you have to select the correct board architecture and port. The board architecture will be "ESP32C6 Dev Module" and the port will be whatever you gave permissions to in step 1, likely `/dev/ttyACM0`.

To connect to the ESP32, use a laptop and connect to the WiFi network the ESP32 is hosting. This is configured in the code and will be explained later in the guide. Using your browser, connect to the IP `192.168.4.1`. You can use the arrow keys on the keyboard to control the ESP32.

- So basically you need to enable "USD CDC On Boot:" and enable "Erase All Flask Before Sketch Upload". Both of these can be found in the tools tab.

# Configuration
The most important configuration options are the WiFi SSID and password. Make these something unique so that they don't conflict with other groups' robots. The secondmost important configuration options are the pins for the motor controller. Make sure that the pins assigned to DIR1, DIR2, PWM1, and PWM2 are correct.

The other optional configuration is outlined in the project file.

# P.S
Shoutout to Mr. Z. Truly a goated teacher.
