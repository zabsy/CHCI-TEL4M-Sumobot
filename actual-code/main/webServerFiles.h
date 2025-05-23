const char index_html[] = R"rawliteral(
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
)rawliteral";

const char main_js[] = R"rawliteral(
document.addEventListener("DOMContentLoaded", () => {
  const URL = "http://192.168.4.1/control";
  let ws = new WebSocket("ws://" + window.location.hostname + ":81/");
  let directionVectors = [0, 0];

  let mapping = {
    ArrowLeft: [0, -1],
    ArrowRight: [0, 1],
    ArrowUp: [1, 1],
    ArrowDown: [1, -1],
  };

  function sendRequest() {
    try {
      let inputs = JSON.stringify({
        x: directionVectors[0],
        y: directionVectors[1],
      });

      ws.send(inputs);
    } catch (e) {
      console.error(e);
    }
  }

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
});
)rawliteral";