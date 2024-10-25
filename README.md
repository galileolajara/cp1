# New programming language aiming to be as simple as C
I noticed that many new languages like Zig, Rust, V, Odin, C3, etc aren't candidates for the most simplest newer language, just like how simple C is among others. So I thought of sharing my own language in the hopes that it others might find it fitting for their search of a simplest newer language. Aside from being simple, it also aims to have very fast incremental compilation.

What does Hello World look like?
-
![hello](/images/helloworld.png)

How to use?
-
Begin by cloning the repo. Make sure to have ninja, clang and re2c installed on your computer.
```
git clone https://github.com/galileolajara/glc.git
cd glc
ninja
```
Then checkout the examples:
```
cd examples/02-methods
ninja
out/methods
```

GLC is a programming language for people who love the simplicity of C language and looking for few modern features absent in C.
-
Why use GLC instead of C?:
- You want shorter codes through use of methods on structs, unions, enums and typedefs.
- You want to organize and shorten (further) your codes using namespaces.
- You build tools and scripts that parses your code, because GLC's syntax is tools-friendly.
- Faster development through very fast compilation speed and very fast incremental compilation.
- Still be able to use C's features and tools because GLC outputs C source files.

GLC compared to Zig, Odin, V, C3, Rust, Cppfront
-
- Strings are just array of chars, just like C.
- No templates, no compile-time execution, just like C. But hey, you can do metaprogramming with scripts, aren't ya?
- No safety features, just like C. But you can use AddressSanitizer and the likes of it, just like in C.
- No built-in memory management, just like C. But feel free to use Boehm GC, just like in C.
- No defer, no inheritance, no run-time polymorphism, just like C. But we have a different kind of polymorphism! Just read more.
- If you think GLC have very few features unlike the other languages, it is because GLC is trying to be fast and simple, just like C!

Primary Objective of GLC
-
The development of GLC started in 2012 when I'm involved in programming games and game servers and needed a language that have fast incremental compilation speed.
During that time, I was a fan of mobile CPUs such as Intel Atom hence GLC was born out of a necessity to really have fast compilation speeds.
If you are searching for a language that compilation speed is #1 problem that's being solved, you might want to try GLC.

How old is GLC?
-
GLC have been around more than a decade but I didn't share it to public because its codebase was written in a very quick and dirty way.
GLC is self-hosted, meaning GLC is written in GLC since 2012. I rewrote GLC with (hopefully) a cleaner codebase around September - October 2024,
and started uploading it here on Github once I got it to self-host for the second time.
