#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#include "webServerFiles.h" // have to do this to fix a bug with the arduino ide preprocessor (i hate arduino ide)

const char* ssid = "ESP32";
const char* password = "Bigman2025";

WebServer server(80);
WebSocketsServer ws = WebSocketsServer(81);

void handle_home_page() {
  server.send(200, "text/html", index_html);
}

void handle_main_js() {
  server.send(200, "text/html", main_js);
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
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.print("\n");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
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
