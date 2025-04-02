#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketServer.h>

const char* ssid = "sumobot-wifi";
const char* password = "password";



String website = "";

WebServer server(80);
WebSocketServer websocket = WebSocketServer(81);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(". ");
  }
  Serial.println("");
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", website);
  });
  server.begin();

  websocket.begin();
  websocket.onEvent(inputListener);
}

void loop() {
  server.handleClient();
  webSocket.loop();
}

void inputListener(byte num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      break;
    case WStype_TEXT:
      break;
  }
}
