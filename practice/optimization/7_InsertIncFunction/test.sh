#!/bin/bash
# DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
src="test"
dirname=${PWD##*/}
lib=${dirname:2}


for compile_opt in "$@"
do
  make
  clang -c -emit-llvm $src.c -o $src.bc | opt -load $lib.so -$compile_opt $src.bc -o $src.opt.bc
  "(llvm-dis $src.opt.bc | llvm-dis $src.bc)" > /dev/null 2>&1
done

