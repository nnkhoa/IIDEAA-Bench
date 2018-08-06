#!/bin/bash
set -x



bellerophon  -objs vpa_n.o -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/kinematics.cpp/4/vpa_n_float_report.csv -t VpaAprx -P gaconfig.param  200.0 
