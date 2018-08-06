#!/bin/bash
set -x 

bellerophon -v -objs vpa.o -objs /usr/lib/libjpeg.so -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/encoder.cpp/5/vpa_float_report.csv -t VpaAprx -P gaconfig.param 150.0
