#!/bin/bash
set -x



bellerophon -v -objs vpa_n.o -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/fourier.cpp/4/vpa_n_float_report.csv -t VpaAprx -P gaconfig.param  200.0
