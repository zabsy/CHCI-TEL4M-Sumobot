#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32";
const char* password = "Bigman2025";

WebServer server(80);

const char index_html[] = R"(
<!doctype html>
<html>
  <head>
    <title>Web Page</title>
    <script src="/main.js"></script>
  </head>
  <body>
    <h2>Control Page</h2>
  </body>
</html>
)";

const char main_js[] = R"(
document.addEventListener("DOMContentLoaded", () => {
  const URL = "http://192.168.4.1/control";
  let directionVectors = [0, 0];

  let mapping = {
    ArrowLeft: [0, -1],
    ArrowRight: [0, 1],
    ArrowUp: [1, 1],
    ArrowDown: [1, -1],
  };

  function handleKey(event) {
    if (!mapping[event.key]) return;
    let [index, direction] = mapping[event.key];
    if (event.type === "keyup") {
      directionVectors[index] = 0;
    } else {
      directionVectors[index] = direction;
    }

    sendRequest();
  }

  window.addEventListener("keydown", handleKey);
  window.addEventListener("keyup", handleKey);

  async function sendRequest() {
    try {
      await fetch(URL, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          x: directionVectors[0],
          y: directionVectors[1],
        }),
      });
    } catch (badStuff) {
      console.error(badStuff);
    }
  }
});
)";

void handle_home_page() {
  server.send(200, "text/html", index_html);
}

void handle_main_js() {
  server.send(200, "application/javascript", main_js);
}

void handle_control() {
  String body = server.arg("plain");

  int xIndex = body.indexOf("x");
  int yIndex = body.indexOf("y");

  int xValue = body.substring(body.indexOf(":", xIndex) + 1, body.indexOf(",", xIndex)).toInt();
  int yValue = body.substring(body.indexOf(":", yIndex) + 1, body.indexOf("}", yIndex)).toInt();

  Serial.printf("Received => x: %d, y: %d\n", xValue, yValue);
  server.send(200, "text/plain", "guccigang");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  Serial.print("Access Point IP: ");
  Serial.println(IP);

  server.on("/", handle_home_page);
  server.on("/main.js", handle_main_js);
  server.on("/control", HTTP_POST, handle_control);

  server.begin();
  Serial.println("Server started...");
}

void loop() {
  server.handleClient();
}
