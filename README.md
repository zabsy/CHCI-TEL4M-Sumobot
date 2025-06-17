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

## Connecting to ESP32 🔥🔥🔥

To see the IP address of your access point, enable the following settings under the `Tools` tab of your `Arduino IDE`:
- `USB CDC On Boot`
- `Erase All Flash Before Sketch Upload`

Once you upload the code, the IP address will appear in the Serial Monitor. Remember this IP Address, it is needed to connect to the ESP32.

### Steps to Connect 🥶🥶🥶
1. Use your laptop to connect to the WiFi network that the ESP32 is hosting. This is configured in the code and will be explained later.
2. In your browser, go to the IP Address you received from the step earlier (usually it will be `192.168.4.1`).
3. You can use the arrow keys on your keyboard to control the ESP32.

# Configuration
The most important configuration options are the WiFi SSID and password. Make these something unique so that they don't conflict with other groups' robots. Also, the WiFi password has to be at least 8 characters long. Don't ask me why, that's just the way it is. The secondmost important configuration options are the pins for the motor controller. Make sure that the pins assigned to DIR1, DIR2, PWM1, and PWM2 are correct.

The other optional configuration is outlined in the project file.

Goodluck to any future student who uses this, dattebayo!

# P.S.
Shoutout to Mr. Z. Truly a goated teacher.
