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