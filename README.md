# llvm-porting
[![Build Status](https://travis-ci.com/llvmphighter/llvm-porting.svg?branch=master)](https://travis-ci.com/llvmphighter/llvm-porting)

This project adds an experimental architecture "**TOY**" to the LLVM backend. Most of codes related to **TOY** are under the lib/Target/TOY.

## Prerequisites
The following command installs gcc/g++ compilers and libraries on Ubuntu Linux 16.04 or later:
```shell
$ sudo apt install build-essential
```
## Build
```shell
$ mkdir <path-to-build-directory> && cd <path-to-build-directory>
$ cmake –DCMAKE_BUILD_TYPE=Debug <path-to-llvm-porting-root>
$ make -j16
```

## Test
The **llc** is a tool to compile the LLVM IR to the assembly language of specific architecture. Therefore, we use **llc** to verify our TOY backend. The **llc** is generated under the `bin` directory after buliding. To use it, you have to append the path of `bin` to the $PATH:

```shell
$ export PATH=<path-to-your-build-directory>/bin/:$PATH 
```

All of the tests of TOY are put under the `toytests` directory. For example,

```shell
$ llc -o basic.s <path-to-llvm-porting-root>/toytests/basic.ll
```

This would generate a basic.s which contains the TOY assembly.

If you want to output the object file, you could type

```shell
$ llc -o basic.o -filetype=obj <path-to-llvm-porting-root>/toytests/basic.ll
```

This would generate an ELF object file named basic.o




