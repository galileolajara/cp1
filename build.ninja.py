out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = clang "): continue
    if line.startswith(" command = gcc "): continue
    out.append(line)
f = open("build-tcc.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = gcc "): continue
    out.append(line)
f = open("build-clang.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = gcc "): continue
    if line.startswith(" command = clang "):
        line = "$flags -fsanitize=address -ggdb".join(line.split("$flags"))
    out.append(line)
f = open("build-clang-debug.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = gcc "): continue
    if line.startswith(" command = clang "):
        line = "$flags -O3 -flto".join(line.split("$flags"))
    out.append(line)
f = open("build-clang-release.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = clang "): continue
    out.append(line)
f = open("build-gcc.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = clang "): continue
    if line.startswith(" command = gcc "):
        line = "$flags -fsanitize=undefined -ggdb".join(line.split("$flags"))
    out.append(line)
f = open("build-gcc-debug.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()

out = []
for line in open("build-template.ninja", "r"):
    if line.startswith(" command = tcc "): continue
    if line.startswith(" command = clang "): continue
    if line.startswith(" command = gcc "):
        line = "$flags -O3 -flto".join(line.split("$flags"))
    out.append(line)
f = open("build-gcc-release.ninja", "wb")
f.write("".join(out).encode("ascii"))
f.close()
