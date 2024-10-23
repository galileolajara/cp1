const fs = require("fs");
const match1 = "`\\glc-decl-var";
const replace1 = "`\\decl-var";
const match2 = "\\glc-decl-var";
const replace2 = "\\decl-var";
for (let fname of fs.readdirSync(".")) {
   if (fname.endsWith(".glc")) {
      /* let lines = fs.readFileSync(fname).toString().split("\n");
      if(lines[1] == "{alias 'c = %stdc}") {
         lines[0] = "{alias 'glc = %glc}\n{alias 'c = %stdc}";
         lines[1] = "{at(%glc)";
      } else {
         lines[0] = "{alias 'glc = %glc}\n{at(%glc)";
      }
      lines.push("}\n");
      fs.writeFileSync(fname, lines.join("\n")); */
      let lines = [];
      for (let line of fs.readFileSync(fname).toString().split("\n")) {
         // line = line.split(":glc-name").join(":glcname");
         if (line.indexOf(match1) != -1) {
            line = line.split(match1).join(replace1);
         } else if (line.indexOf(match2) != -1) {
            line = line.split(match2).join(replace2);
         }
         // line = line.split(":glcname").join(":glc-name");
         lines.push(line);
         /* let line_after = line.split("'glc\\include").join("\\glc-include");
         if (line_after != line) {
            console.log(fname, line_after);
         }
         lines.push(line_after); */
      }
      fs.writeFileSync(fname, lines.join("\n"));
   }
}
