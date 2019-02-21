window.onload = init;

let context;
let x = 100;
let y = 200;
let dx = 5;
let dy = 5;

function init() {
    const myCanvas = document.getElementById("myCanvas");
    context = myCanvas.getContext('2d');
    setInterval(draw, 10);
}

function draw() {
    context.clearRect(0, 0, 500, 600);
    context.beginPath();
    context.fillStyle = "#0000ff";
    // Draws a circle of radius 20 at the coordinates 100,100 on the canvas
    context.arc(x, y, 20, 0, Math.PI * 2, true);
    context.closePath();
    context.fill();
    // Boundary Logic
    if (x < 0 || x > 500) dx = -dx;
    if (y < 0 || y > 500) dy = -dy;
    x += dx;
    y += dy;
}