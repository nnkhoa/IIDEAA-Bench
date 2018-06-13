#include<iostream>
#include<fstream>
#include<math.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;

#include "blackscholes.hpp"

extern "C" double BELLERO_getError() {
	const char* inputPath = "/opt/ax_blackscholes/test.data/input/blackscholesTrain_100K.data";
	const char* outputPath = "/opt/ax_blackscholes/src/build/output.txt";
	::std::ifstream oracle ("/opt/ax_blackscholes/src/build/oracle.txt");
	
	//Axproximate version of the function from the mutated file
	
	doWork(inputPath, outputPath);

	::std::ifstream axc (outputPath);
	if (!oracle.good()) {
		::std::cerr << "The orcale does not exist!\n";
		exit(1);
	}
	if (!axc.good()) { 
		::std::cerr << "The output does not exist!\n";
		exit(1);
	}

	double avgError = 0.0;
	double error = 0.0;
	double absError = 0.0;
	int count = 0;

	double gResult;
	double axResult;
	double diff;

	while(!oracle.eof() && !axc.eof()) {
		oracle >> gResult;
		axc >> axResult;
		
		diff = gResult - axResult;
		error = sqrt(diff*diff);
		
		if (gResult == 0) {
			absError += 1;
		} else if ( isnan(error) || isnan(gResult)) {
			absError += 1;			
		} else if ((error/gResult) > 1) {
			absError += 1;
		}else {
			absError += (error/gResult);
		}
		//::std::cout << error << " " << gResult << "\n";
		//absError += (error/gResult);
		count++;
	}

	avgError = absError/count;

	return avgError;
}
