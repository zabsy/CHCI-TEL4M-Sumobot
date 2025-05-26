#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#include "webServerFiles.h" // have to do this to fix a bug with the arduino ide preprocessor (i hate arduino ide)

const int PWM1 = 5;
const int PWM2 = 14;
const int DIR1 = 4;
const int DIR2 = 15;

const char* ssid = "ESP32";
const char* password = "Bigman2025";

void controlMotors(int dir1State, int dir2State, int speed1, int speed2) {
  digitalWrite(DIR1, dir1State);
  digitalWrite(DIR2, dir2State);
  analogWrite(PWM1, speed1);
  analogWrite(PWM2, speed2);
}

WebServer server(80);
WebSocketsServer ws = WebSocketsServer(81);

float prevX, prevY;

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

      x=(x==0 ? 0: x<0 ? -1: 1);
      y=(y==0 ? 0: y<0 ? -1: 1);
      
      controlMotors(x<0 ? LOW: HIGH, y<0 ? LOW: HIGH, x==0 ? 0:255, y==0 ? 0:255);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  prevX = 0;
  prevY = 0;

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

void loop() {
  server.handleClient();
  ws.loop();
}

