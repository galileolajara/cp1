const fs = require("fs");
let txt = fs.readFileSync(process.argv[2]).toString();
let compiler = [];
let parser = [];
let mode = 0;
for (let line of txt.split("\n")) {
   if (mode == 0) {
      if (line == "if-compiler") {
         mode = 1;
         compiler.push("");
         parser.push("");
      } else if (line == "if-parser") {
         mode = 2;
         compiler.push("");
         parser.push("");
      } else {
         compiler.push(line);
         parser.push(line);
      }
   } else if (mode == 1) {
      if (line == "end-if") {
         mode = 0;
         compiler.push("");
         parser.push("");
      } else {
         compiler.push(line);
         parser.push("");
      }
   } else if (mode == 2) {
      if (line == "end-if") {
         mode = 0;
         compiler.push("");
         parser.push("");
      } else {
         compiler.push("");
         parser.push(line);
      }
   }
}
fs.writeFileSync(process.argv[3], compiler.join("\n"));
fs.writeFileSync(process.argv[4], parser.join("\n"));
