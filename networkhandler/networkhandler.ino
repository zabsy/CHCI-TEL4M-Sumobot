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
          console.log("Initializing WebSocket connection...");
          socket = new WebSocket("ws://" + window.location.hostname + ":81/");

          socket.addEventListener("open", () => {
            console.log("WebSocket connection opened.");
          });

          socket.addEventListener("message", (event) => {
            console.log("Message received from server:", event.data);
          });

          socket.addEventListener("close", () => {
            console.log("WebSocket connection closed.");
          });

          socket.addEventListener("error", (error) => {
            console.error("WebSocket error:", error);
          });

          window.addEventListener(
            "gamepadconnected",
            (e) => {
              console.log("Gamepad connected event.");
              const gp = navigator.getGamepads()[e.gamepad.index];
              console.log(
                `Gamepad connected at index ${gp.index}: ${gp.id} has ${gp.buttons.length} buttons and ${gp.axes.length} axes.`,
              );
              controllerConnected = true;
              inputHandler();
            },
            false,
          );

          window.addEventListener(
            "gamepaddisconnected",
            (e) => {
              console.log("Gamepad disconnected.");
              controllerConnected = false;
            },
            false,
          );
        }

        function inputHandler() {
          if (!controllerConnected) {
            console.log("No controller connected.");
            return;
          }

          const gamepads = navigator.getGamepads();
          const gp = gamepads[0];

          if (!gp) {
            console.log("No gamepad detected.");
            return;
          }

          let buttons = ["buttons"];
          let axes = ["axes"];

          for (let i = 0; i < gp.buttons.length; i++) {
            if (gp.buttons[i].pressed) {
              console.log(`Button ${i} pressed with value ${gp.buttons[i].value}`);
              buttons.push([i, gp.buttons[i].value]);
            }
          }

          for (let i = 0; i < gp.axes.length; i++) {
            if (Math.abs(gp.axes[i]) > 0.1) {
              console.log(`Axis ${i} moved to ${gp.axes[i]}`);
              axes.push([i, gp.axes[i]]);
            }
          }

          if (buttons.length > 1) {
            console.log("Sending buttons:", buttons);
            socket.send(JSON.stringify(buttons));
          }

          if (axes.length > 1) {
            console.log("Sending axes:", axes);
            socket.send(JSON.stringify(axes));
          }

          requestAnimationFrame(inputHandler);
        }

        window.onload = () => {
          console.log("Window loaded.");
          init();
        };

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
