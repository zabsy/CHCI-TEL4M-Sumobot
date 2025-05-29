#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#include "webServerFiles.h" // have to do this to fix a bug with the arduino ide preprocessor (i hate arduino ide)

#define PWM1 5 // pin controlling the speed of motor 1
#define PWM2 14 // pin controlling the speed of motor 2
#define DIR1 4 // pin controlling the direction of motor 1
#define DIR2 15 // pin controlling the direction of motor 2

const char* ssid = "ESP32"; // wifi access point name, change to something unique
const char* password = "Bigman2025"; // password for your network

// x and y are mapped to the x-axis (left and right arrows) and 
// y-axis (up and down arrows) respectively. For example pressing up and left will
// output x = -1 and y = 1
// modify this function to map the inputs to different 
void map_input(int x, int y) {
  if (y == 0) {
    if (x != 0) {
      bool is_right = x > 0;
      control_motors(is_right ? LOW : HIGH, is_right ? HIGH : LOW, 255, 255);
    }
  }
  else {
    bool is_up = y > 0;
    if (x == 0) {
      control_motors(is_up ? HIGH : LOW, is_up ? HIGH : LOW, 255, 255);
    }
    else {
      bool is_right = x > 0;
      control_motors(is_up ? HIGH : LOW, is_up ? HIGH : LOW, is_right ? 50 : 255, is_right ? 255 : 50);
    }
  }

  if (y == 0 && x == 0) {
    control_motors(HIGH, HIGH, 0, 0);
  }
}

// this function takes 4 parameters; the direction for motor 1, direction for 
// motor 2, speed for motor 1, and speed for motor 2.
// the direction parameters take either HIGH or LOW which make the motor spin in 
// opposite directions. the speed parameters range between 0 and 255.
void control_motors(int dir1State, int dir2State, int speed1, int speed2) {
  digitalWrite(DIR1, dir1State);
  digitalWrite(DIR2, dir2State);
  analogWrite(PWM1, speed1);
  analogWrite(PWM2, speed2);
}

WebServer server(80);
WebSocketsServer ws = WebSocketsServer(81);

void handle_home_page() {
  server.send(200, "text/html", index_html);
}

void handle_main_js() {
  server.send(200, "applications/javascript", main_js);
}

void handle_control(byte num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("Client " + String(num) + " connected.");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Client " + String(num) + " disconnected.");
      break;
    case WStype_TEXT:
      JsonDocument doc;
      DeserializationError error = deserializeJson(doc, payload);
      float x = doc["x"];
      float y = doc["y"];
      map_input(x, y);
      break;
  }
}

void setup() { // dont touch this
  Serial.begin(115200);
  while (!Serial);

  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  Serial.print("Access Point IP: ");
  Serial.println(IP);

  server.on("/", handle_home_page);
  server.on("/main.js", handle_main_js);

  server.begin();
  ws.begin();
  ws.onEvent(handle_control);
  Serial.println("Server started...");
}

void loop() { // dont touch this either
  server.handleClient();
  ws.loop();
}
