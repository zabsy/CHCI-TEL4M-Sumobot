#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "sumobot-wifi";
const char* password = "password";

String website = R"(<!DOCTYPE html>
<html>
    <head>
        <title>Sumobot Controller</title>
        <script>
            let socket;
let controllerConnected = false;

function init() {
    socket = new WebSocket('ws://' + window.location.hostname + ':81/');

    window.addEventListener("gamepadconnected", (e) => {
        console.log("Gamepad connected.");
        const gp = navigator.getGamepads()[e.gamepad.index];
        console.log(`Gamepad connected at index ${gp.index}: ${gp.id} has ${gp.buttons.length} buttons and ${gp.axes.length} axes.`);
        controlleCconnected = true;
        inputHandler();
    }, false);
    
    window.addEventListener("gamepaddisconnected", (e) => {
        controllerConnected = false;
        console.log("Gamepad disconnected.");
    }, false);
}

function inputHandler() {
    if (connected) {
        const gamepads = navigator.getGamepads();

        const gp = gamepads[0];
        let buttons = [0];
        let axes = [1];
        for (let i = 0; i < gp.buttons.length; i++) {
            if (gp.buttons[i].pressed)
                buttons.push([i, gp.buttons[i].value]);
        }
        for (let i = 0; i < gp.axes.length; i++) {
            if (Math.abs(gp.axes[i].value) > 0.1) 
                axes.push([i, gp.axes[i].value]);
        }
        if (buttons.length > 1)
            socket.send(buttons);
        if (axes.length > 1)
            socket.send(axes);

        requestAnimationFrame(inputHandler);
    }
}

window.onload = () => {
    init();
}
        </script>
    </head>
    <body>
        
    </body>
</html>)";

WebServer server(80);
WebSocketsServer websocket = WebSocketsServer(81);

void setup() {
  Serial.begin(9600);
  Serial.println("test");
  WiFi.softAP(ssid, password);

  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(1000);
  //  Serial.print(". ");
  //}
  Serial.println("");
  Serial.print("Connected to network with IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", website);
  });
  server.begin();

  websocket.begin();
  websocket.onEvent(inputListener);
}

void loop() {
  server.handleClient();
  websocket.loop();
}

void inputListener(byte num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Client " + String(num) + " has disconnected.");
      break;
    case WStype_CONNECTED:
      Serial.println("Client " + String(num) + " has disconnected.");
      break;
    case WStype_TEXT:
      break;
  }
}
