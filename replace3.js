let files = [];
const fs = require("fs");
for (let fn of fs.readdirSync("glc")) {
   if (fn.endsWith(".glc")) {
      files.push("glc/" + fn);
   }
}
for (let fn of fs.readdirSync("stdc")) {
   if (fn.endsWith(".glc")) {
      files.push("stdc/" + fn);
   }
}
//files = ["glc/enum.glc"];
for (let fn of files) {
   let txt = fs.readFileSync(fn).toString();
   let lines = [];
   for (let line of txt.split("\n")) {
      let origline = line;
      let fdecl = line.indexOf("{{");
      if (fdecl != -1) {
         let close = line.indexOf("}");
         if (close == -1) {
            console.log("} not found");
            process.exit();
         }
         line = line.substring(0, fdecl) + line.substring(fdecl + 1, close) + line.substring(close + 1);
      } else {
         line = line.replace("inline;", "inline");
      }
      lines.push(line);
   }
   fs.writeFileSync(fn, lines.join("\n"));
}
