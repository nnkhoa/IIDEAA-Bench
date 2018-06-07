#include<iostream>
#include<fstream>
#include<math.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;

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

	double WCE = 0.0;
	double tmp;

	double greal, gima;
	double axreal, axima;
	double diffreal, diffimg;

	while(!oracle.eof() && !axc.eof()){
		oracle >> greal >> gima;
		axc >> axreal >> axima;
		diffreal = greal - axreal;
		diffimg = gima - axima;

		tmp = sqrt((diffreal*diffreal) + (diffimg*diffimg));

		if (tmp > WCE) 
			WCE = tmp;
	}

	return WCE;
}
