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
      if (event.keyCode == 38)
        document.getElementById("w").style.fontWeight = "normal";
      else if (event.keyCode == 37)
        document.getElementById("a").style.fontWeight = "normal";
      else if (event.keyCode == 40)
        document.getElementById("s").style.fontWeight = "normal";
      else if (event.keyCode == 39)
        document.getElementById("d").style.fontWeight = "normal";
    } else {
      directionVectors[index] = direction;
      if (event.keyCode == 38)
        document.getElementById("w").style.fontWeight = "bold";
      else if (event.keyCode == 37)
        document.getElementById("a").style.fontWeight = "bold";
      else if (event.keyCode == 40)
        document.getElementById("s").style.fontWeight = "bold";
      else if (event.keyCode == 39)
        document.getElementById("d").style.fontWeight = "bold";
    }

    sendRequest();
  }

  window.addEventListener("keydown", handleKey);
  window.addEventListener("keyup", handleKey);
});
