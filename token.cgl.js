const fs = require("fs");
let lines = ["{at(%glc)", "{:token[", "#nil,"];
let txt = fs.readFileSync("out/cgl_parser.h").toString();
for (let line of txt.split("\n")) {
   if (line == "") continue;
   lines.push("#" + line.substring(18, line.indexOf(" ", 19)).toLowerCase().split("_").join("-") + ",");
}
lines.push("]:int");
lines.push("{cgl-name(e:this):char[] @cgl-name}");
lines.push("}");
lines.push("}\n");
fs.writeFileSync("out/token.cgl", lines.join("\n"));
