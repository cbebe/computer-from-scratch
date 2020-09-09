const SCREENVAR = 0x3000;
// FIREFOX CANT HANDLE THIS
const RAM = Array(0x10000).fill(SCREENVAR);

const myScreen = <HTMLCanvasElement>document.getElementById("screen");
const ctx = <CanvasRenderingContext2D>myScreen.getContext("2d");

console.log(ctx);
for (let i = 0; i < 100; ++i) {
  ctx.fillStyle = "#FFF";
  ctx.fillRect(256 + i - 1, 128 + i - 1, 10, 10);
  ctx.fillStyle = "#000";
  ctx.fillRect(256 + i, 128 + i, 10, 10);
}

document.getElementById("fill")?.addEventListener("click", e => {
  console.time("fill");
  RAM.forEach((word, i) => {
    console.log(word + i);
  });
  console.timeEnd("fill");
});
