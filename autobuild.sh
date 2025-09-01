#!/bin/bash

set -e

# 指定编译器，保持和vscode一致
export CC=/usr/local/gcc-11.2.0/bin/gcc
export CXX=/usr/local/gcc-11.2.0/bin/g++

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
cd ..
cp -r `pwd`/src/include `pwd`/lib