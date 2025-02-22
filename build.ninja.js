const fs = require("fs");
let out;
let lines = fs.readFileSync("build-template.ninja").toString().split("\n");
out = [];
for (let line of lines) {
   if (line.startsWith(" command = clang ")) continue;
   if (line.startsWith(" command = gcc ")) continue;
   out.push(line + "\n");
}
fs.writeFileSync("build-tcc.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = gcc ")) continue;
   out.push(line + "\n");
}
fs.writeFileSync("build-clang.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = gcc ")) continue;
   if (line.startsWith(" command = clang ")) {
      out.push(line.split("$flags").join("$flags -ggdb") + "\n");
   } else {
      out.push(line + "\n");
   }
}
fs.writeFileSync("build-clang-debug.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = gcc ")) continue;
   if (line.startsWith(" command = clang ")) {
      out.push(line.split("$flags").join("$flags -O3 -flto") + "\n");
   } else {
      out.push(line + "\n");
   }
}
fs.writeFileSync("build-clang-release.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = clang ")) continue;
   out.push(line + "\n");
}
fs.writeFileSync("build-gcc.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = clang ")) continue;
   if (line.startsWith(" command = gcc ")) {
      out.push(line.split("$flags").join("$flags -ggdb") + "\n");
   } else {
      out.push(line + "\n");
   }
}
fs.writeFileSync("build-gcc-debug.ninja", out.join(""));
out = [];
for (let line of lines) {
   if (line.startsWith(" command = tcc ")) continue;
   if (line.startsWith(" command = clang ")) continue;
   if (line.startsWith(" command = gcc ")) {
      out.push(line.split("$flags").join("$flags -O3 -flto") + "\n");
   } else {
      out.push(line + "\n");
   }
}
fs.writeFileSync("build-gcc-release.ninja", out.join(""));
