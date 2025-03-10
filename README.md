## What does Hello World (with Metaprogramming) look like?
![hello](/images/helloworld-2025-02-26.5.png)

How to use?
-
```
git clone https://github.com/galileolajara/cp1
cd cp1

# On Windows, no need to build. Pre-built .exe are in the bin folder

# On Linux, macOS, or BSD, run one of the following:
make -f Makefile-tcc # to build using TCC
make -f Makefile-clang # to build using Clang
make -f Makefile-gcc # to build using GCC
```

Then checkout the examples:
```
# On Windows:
bin\cp1-run examples/01-hello.cp1 # To run hello world
bin\cp1-compile -c hello.c examples/01-hello.cp1 # To see the C code

# On Linux, macOS, or BSD:
bin/cp1-run examples/01-hello.cp1 # To run hello world
bin/cp1-compile -c hello.c examples/01-hello.cp1 # To see the C code
```

On Linux, macOS or BSD, if you want to build Cp1 using the .cp1 files, you need ninja and re2c installed. Then run one of the following:
```
ninja -f build-tcc.ninja # to build using TCC
ninja -f build-clang.ninja # to build using Clang
ninja -f build-gcc.ninja # to build using GCC
```
Top 1 Feature: Easy-to-use yet powerful metaprogramming system
-
- Metaprogramming is just as easy as *string intepolation*. Uses QuickJS of Fabrice Bellard (who made TCC).
- Metaprograms are cached and have few or *zero overhead*.
- Debugging metaprograms is *easier* because you can see the output of metaprograms in the cache folder.

Top 2 Feature: Fast compilation speeds
-
- Took *incremental compilation* seriously. Up to 125K lines of codes per second on Macbook M2.
- Codes are *cached and never parsed again*.
- Cp1 can build itself in *0.1 seconds* using TCC on Macbook M2.

Top 3 Feature: Shorter codes
-
- *Function arguments* can be used to declare variables.
- Enums, primitive types and literals *also have methods*.
- Meta-methods can help you *implement printf-like functionality* easily.

Cp1 means C+1 or C plus 1, named just like C++ or C plus plus
-
- Cp1 is a very thin abstraction on top of C. Think of it as a TypeScript for C. The +1 in the name suggests that the thin abstraction is just the bare essentials to equip C some of the modern features today such as support for metaprogramming, methods on enums, structs and even the primitive types, support for C++'s auto keyword for variables, namespaces, modules and more.
- Cp1 is vastly different from Zig, Odin, C3, Rust, Vlang because Cp1 aims to maintain only few features but these few features are carefully selected to allow you to do a lot of things when these features are combined.
- Also, Cp1's top priority is compilation speed, similar to Vlang. Cloning the repo and building it for the first time using build-tcc.ninja takes 0.1s on Macbook Pro M2 with Fedora Asahi Remix (Linux OS). Editing a source file of Cp1 then recompiling (incremental compilation) takes 0.05s.

Join us on Discord!
-
[![Discord](https://dcbadge.vercel.app/api/server/qBtunCNyUS)](https://discord.gg/qBtunCNyUS)
