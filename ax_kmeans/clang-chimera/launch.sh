#!/bin/bash
set -x

clang-chimera -v -debug -fun-op conf.csv -generate-mutants ../src/segmentation.cpp -cd-dir ../src/build -o output -- -std=c++11 -I../code/include -I../code/include/segmantation
