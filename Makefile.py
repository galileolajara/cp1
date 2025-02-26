out = []
for line in open("Makefile-template", "r"):
    if line.startswith("\tclang "): continue
    if line.startswith("\tgcc "): continue
    out.append(line)
f = open("Makefile-tcc", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("Makefile-template", "r"):
    if line.startswith("\ttcc "): continue
    if line.startswith("\tgcc "): continue
    out.append(line)
f = open("Makefile-clang", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("Makefile-template", "r"):
    if line.startswith("\ttcc "): continue
    if line.startswith("\tclang "): continue
    out.append(line)
f = open("Makefile-gcc", "wb")
f.write("".join(out).encode("ascii"))
f.close()
