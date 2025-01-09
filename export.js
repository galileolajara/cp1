const fs = require("fs");
let txt_split = fs.readFileSync(process.argv[2]).toString().split("\n");
let funcs = [];
let lines = [];
let get = false;
for (let line of txt_split) {
   if (line == "void _Nglc_Pexport_0() {") {
      get = true;
   } else if (get) {
      if (line == "}") {
         break;
      }
      funcs[line.split("(")[0]] = true;
   }
}
let indent = 0;
for (let line of txt_split) {
   if (line.endsWith("{")) {
      indent++;
   } else if (line.endsWith("}") || line.endsWith("};")) {
      indent--;
   } else if (indent == 0) {
      if (line.endsWith(");")) {
         let name = line.split("(")[0];
         name = name.split(" ");
         name = name[name.length - 1];
         if (name in funcs) {
            lines.push(line);
            delete funcs[name];
         }
      }
   }
}
lines.push("");
fs.writeFileSync(process.argv[3], lines.join("\n"));
