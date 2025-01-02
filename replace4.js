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
   txt = txt.replace(/{gvar[^}]*/g, function(a, b, c) {
      // console.log(a);
      return a.replace(/\.[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*/g, function(a, b, c) {
         // console.log(" " + a);
         return a.substr(1);
      });
   });
   txt = txt.replace(/{:[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*([^)]*)/g, function(a, b, c) {
      // console.log(a);
      return a.replace(/\.[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*/g, function(a, b, c) {
         // console.log(" " + a);
         return a.substr(1);
      });
   });
   let lines = [];
   for (let line of txt.split("\n")) {
      let origline = line;
      line = line.replace(/\/[a-zA-Z0-9]+(-[a-zA-Z0-9]+)*/, function(a, b, c) {
         return ':' + a.substr(1);
      });
      let ret = line.indexOf("{return");
      if (ret != -1) {
         let ret_end = line.indexOf("}", ret);
         line = line.substring(0, ret) + ":return" + line.substring(ret + 7, ret_end) + ";" + line.substring(ret_end + 1);
      }
      if (line != origline) {
         console.log(origline);
         console.log(line);
      }
      line = line.replace(";}", "}");
      lines.push(line);
   }
   fs.writeFileSync(fn, lines.join("\n"));
}
