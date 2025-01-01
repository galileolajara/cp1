const fs = require("fs");
let lines = ["{at(%glc)", "{\\token(", "#nil,"];
let txt = fs.readFileSync("out/glc_parser.h").toString();
for (let line of txt.split("\n")) {
   if (line == "") continue;
   lines.push("#" + line.substring(18, line.indexOf(" ", 19)).toLowerCase().split("_").join("-") + ",");
}
lines.push("):int");
lines.push("{glc-name(e:this):char[] @glc-name}");
lines.push("}");
lines.push("}\n");
fs.writeFileSync("out/token.glc", lines.join("\n"));
