#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <time.h>

#include "vpa.h"
#include "mushroom.h"

#define AX_MODE 1

//bool vpa_n::VPA::UPCASTING = false;

const char* axPath = "/opt/fann_iideaa/fann_mushroom/src/build/ax";
const char* oraclePath = "/opt/fann_iideaa/fann_mushroom/src/build/oracle";
clock_t time_start, time_end;

void doAxCompute() {
	if (doMushroom(AX_MODE) != 0) {
		::std::cerr << "Error Executing Approximate Version of the program\n";
		exit(-1);
	}
}

extern "C" double BELLERO_getError() {
	float oracleMSE, axMSE, diff;

	//execute Ax computation
	time_start = clock();
	doAxCompute();
	time_end = clock();
	//load result
	::std::ifstream oracle (oraclePath);
	::std::ifstream axc (axPath);
	while(!oracle.eof() && !axc.eof()){
		oracle >> oracleMSE;
		axc >> axMSE;
		
		diff = 100 * ((axMSE - oracleMSE)/oracleMSE);

		
	}
	//return MSE
	return diff;

}

extern vpa::FloatingPointPrecision OP_0, OP_1, OP_2, OP_3, OP_4;

extern "C" double BELLERO_Reward() {
	double rew = 0;

	//  MantType mant;
	int gradeMant[5];
	int gradeExp[5];

	gradeMant[0] = 23 - OP_0.mant_size;
	gradeMant[1] = 23 - OP_1.mant_size;
	gradeMant[2] = 23 - OP_2.mant_size;
	gradeMant[3] = 23 - OP_3.mant_size;
	gradeMant[4] = 23 - OP_4.mant_size;
	
	gradeExp[0] = 8 - OP_0.exp_size;
	gradeExp[1] = 8 - OP_1.exp_size;
	gradeExp[2] = 8 - OP_2.exp_size;
	gradeExp[3] = 8 - OP_3.exp_size;
	gradeExp[4] = 8 - OP_4.exp_size;
	
	for(int i = 0; i < 6; i++)
		rew+=gradeMant[i]+gradeExp[i];
//printf("Reward: %g\n\n", rew);
	return rew;
}

extern "C" double BELLERO_Penality() {
	return (time_end - time_start)/(double)CLOCKS_PER_SEC;
}