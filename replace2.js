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
   txt = txt.replace(/{:[a-z0-9]+(-[a-z0-9]+)*\(?/g, function(a, b, pos) {
      return "{" + a.substr(2);
   });
   fs.writeFileSync(fn, txt);
}
