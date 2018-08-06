#include<iostream>
#include<fstream>
#include<math.h>

#include "vpa.h"
// bool vpa_n::VPA::UPCASTING = false;

#include "fft.hpp"

extern "C" double BELLERO_getError(){
	const int inputParam = 32768;
	const char* outputPath = "/opt/ax_fft/src/build/output.txt";
	::std::ifstream oracle ("/opt/ax_fft/src/build/oracle.txt");
	
	//Axproximate version of the function from the mutated file
	
	doWork(inputParam, outputPath);

	::std::ifstream axc (outputPath);
	if (!oracle.good()){
		::std::cerr << "The orcale does not exist!\n";
		exit(1);
	}
	if (!axc.good()){
		::std::cerr << "The output does not exist!\n";
		exit(1);
	}

	double avgError = 0.0;
	double error = 0.0;
	double absError = 0.0;
	double denominator = 0.0;
	int count = 0;

	double greal, gima;
	double axreal, axima;
	double diffreal, diffimg;

	while(!oracle.eof() && !axc.eof()){
		oracle >> greal >> gima;
		axc >> axreal >> axima;
		diffreal = greal - axreal;
		diffimg = gima - axima;

		error = sqrt((diffreal*diffreal) + (diffimg*diffimg));
		denominator = sqrt((greal*greal) + (gima*gima));

		absError += (error/denominator);
		count++;
	}
	
	avgError = (double)absError/count;

	return avgError;
}

extern vpa::FloatingPointPrecision OP_0, OP_1, OP_2, OP_3, OP_4, OP_5, OP_6, OP_7, OP_8, OP_9, OP_10, OP_11, OP_12, OP_13, OP_14, OP_15, OP_16;

extern "C" double BELLERO_Reward()
{
	double rew = 0;

	//  MantType mant;
	int gradeMant[17];
	int gradeExp[17];

	gradeMant[0] = 54 - OP_0.mant_size;
	gradeMant[1] = 54 - OP_1.mant_size;
	gradeMant[2] = 54 - OP_2.mant_size;
	gradeMant[3] = 54 - OP_3.mant_size;
	gradeMant[4] = 54 - OP_4.mant_size;
	gradeMant[5] = 54 - OP_5.mant_size;
	gradeMant[6] = 54 - OP_6.mant_size;
	gradeMant[7] = 54 - OP_7.mant_size;
	gradeMant[8] = 54 - OP_8.mant_size;
	gradeMant[9] = 54 - OP_9.mant_size;
	gradeMant[10] = 54 - OP_10.mant_size;
	gradeMant[11] = 54 - OP_11.mant_size;
	gradeMant[12] = 54 - OP_12.mant_size;
	gradeMant[13] = 54 - OP_13.mant_size;
	gradeMant[14] = 54 - OP_14.mant_size;
	gradeMant[15] = 54 - OP_15.mant_size;
	gradeMant[16] = 54 - OP_16.mant_size;
    
	gradeExp[0] = 11 - OP_0.exp_size;
	gradeExp[1] = 11 - OP_1.exp_size;
	gradeExp[2] = 11 - OP_2.exp_size;
	gradeExp[3] = 11 - OP_3.exp_size;
	gradeExp[4] = 11 - OP_4.exp_size;
	gradeExp[5] = 11 - OP_5.exp_size;
	gradeExp[6] = 11 - OP_6.exp_size;
	gradeExp[7] = 11 - OP_7.exp_size;
	gradeExp[8] = 11 - OP_8.exp_size;
	gradeExp[9] = 11 - OP_9.exp_size;
	gradeExp[10] = 11 - OP_10.exp_size;
	gradeExp[11] = 11 - OP_11.exp_size;
	gradeExp[12] = 11 - OP_12.exp_size;
	gradeExp[13] = 11 - OP_13.exp_size;
	gradeExp[14] = 11 - OP_14.exp_size;
	gradeExp[15] = 11 - OP_15.exp_size;
	gradeExp[16] = 11 - OP_16.exp_size;

	for(int i = 0; i < 17; i++)
		rew+=gradeMant[i]*gradeMant[i]+gradeExp[i];
//printf("Reward: %g\n\n", rew);
	return rew;
}
