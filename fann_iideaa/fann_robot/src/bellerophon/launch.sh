#!/bin/bash
set -x 

bellerophon  -objs vpa.o -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/fann_train.cpp/4/vpa_n_float_report.csv -t VpaAprx -P gaconfig.param 200.0
