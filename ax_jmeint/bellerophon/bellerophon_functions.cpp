#include<iostream>
#include<fstream>
#include<math.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;

#include "jmeint.hpp"

extern "C" double BELLERO_getError(){
	const char* inputData = "test.data/input/jmeint_1000K.data";
	const char* outputPath = "/opt/ax_jmeint/src/build/output.txt";
	::std::ifstream oracle ("/opt/ax_jmeint/src/build/oracle.txt");
	
	//Axproximate version of the function from the mutated file
	
	jMeint(inputData, outputPath);

	::std::ifstream axc (outputPath);
	if (!oracle.good()){
		::std::cerr << "The orcale does not exist!\n";
		exit(1);
	}
	if (!axc.good()){
		::std::cerr << "The output does not exist!\n";
		exit(1);
	}

	double missRate = 0.0;
	int count = 0;
	int miss = 0;
	int oValue, axValue;

	while(!oracle.eof() && !axc.eof()){
		oracle >> oValue;
		axc >> axValue;
		
		if (oValue != axValue) {
			miss++;
		}

		count++;
	}
	
	missRate = (double) miss/count;
	::std::cout << missRate << "\n";
	return missRate;
}
