#!/bin/bash
set -x



bellerophon  -objs vpa.o -libdb ../src/build/ -cd-dir ./ -r ../clang-chimera/output/mutants/kinematics.cpp/5/vpa_float_report.csv -t VpaAprx -P gaconfig.param  200.0 
