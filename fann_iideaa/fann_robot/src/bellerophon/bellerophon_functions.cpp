#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

#include "vpa.h"
#include "robot.h"

#define AX_MODE 1

//bool vpa_n::VPA::UPCASTING = false;

const char* axPath = "/opt/fann_iideaa/fann_robot/src/build/ax";
const char* oraclePath = "/opt/fann_iideaa/fann_robot/src/build/oracle";

void doAxCompute() {
	if (doRobot(AX_MODE) != 0) {
		::std::cerr << "Error Executing Approximate Version of the program\n";
		exit(-1);
	}
}

extern "C" double BELLERO_getError() {
	float oracleMSE, axMSE, diff;

	//execute Ax computation
	doAxCompute();

	//load result
	::std::ifstream oracle (oraclePath);
	::std::ifstream axc (axPath);
	while(!oracle.eof() && !axc.eof()){
		oracle >> oracleMSE;
		axc >> axMSE;
		
		diff = 100 * (abs(oracleMSE - axMSE)/oracleMSE);
	}
	//return MSE
	return diff;

}
