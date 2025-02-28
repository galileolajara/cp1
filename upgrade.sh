#!/bin/sh
cp compile2.c compile.c
cp parse2.c parse.c
cp out/export.h export.h
cp out/lex.c lex.c
cp out/preprocess.cp1.c preprocess.cp1.c
cp out/cp1_parse.c cp1_parse.c
cp out/parse2.cp1.c parse.cp1.c
cp out/compile2.cp1.c compile.cp1.c
cp out/run2.cp1.c run.cp1.c
cp out/build-crc32c.h build-crc32c.h
cp hashtable2.c hashtable.c
rm -rf cp1-tmp-* out bin/cp1-parse bin/cp1-run bin/cp1-compile bin/cp1-qjs
