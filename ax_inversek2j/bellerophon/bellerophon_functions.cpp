#include<iostream>
#include<fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;



#include "inversek2j.hpp" // function definition

double toDouble(::std::string numberString){
	int len = numberString.size();
	char* charArray = new char [len+1];
	memset(charArray, 0, len + 1);
	strcpy (charArray, numberString.c_str());

	return atof(charArray);
}

extern "C" double BELLERO_getError() {    
    const char* inputPath = "/opt/ax_inversek2j/test.data/input/theta_1000K.data";
    const char* outputPath = "/opt/ax_inversek2j/src/build/output.txt";
    ::std::ifstream oracle ( "/opt/ax_inversek2j/src/build/oracle.txt" );
	
    doWork(inputPath, outputPath); 

    ::std::ifstream axc ( "/opt/ax_inversek2j/src/build/output.txt" );
    if ( !oracle.good() ) {
        ::std::cerr << "The oracle does not exist!\n";
        exit ( 1 );

    }
   if ( !axc.good() ) {
        ::std::cerr << "The output does not exist!\n";
        exit ( 1 );

    }
	int count = 0;

	double absError = 0.0;
	double nominator, denominator, error;
	
	::std::string oValue0, oValue1;
	::std::string axValue0, axValue1;
	double diff0, diff1;
	
	::std::cout << "Calculating Error: \n";	
	while (!oracle.eof () && !axc.eof()) {
		//::std::cout << count << "\n";	
		oracle >> oValue0 >> oValue1;
		axc >> axValue0 >> axValue1;
		
		//::std::cout << oValue0 << " " << oValue1 << "\n";
		
		//check if any value is NaN
		if (oValue0.compare("nan") == 0 || oValue1.compare("nan") == 0 || axValue0.compare("nan") == 0 || axValue1.compare("nan") == 0) {
			::std::cout << "NaN\n";
			count ++;
			absError += 1;
			continue;
		} 
		
		//calculate abs error
		diff0 =  (toDouble(oValue0) - toDouble(axValue0))  ;
		diff1 = (toDouble(oValue1) - toDouble(axValue1));

		nominator = sqrt(pow(diff0, 2) + pow(diff1, 2));
		denominator = sqrt(pow(toDouble(oValue0), 2) + pow(toDouble(oValue1), 2));
		
		if (denominator == 0) {
			error = 1.0;
		}else if (nominator > denominator) {
			error = 1.0;
		}else {
			error = nominator/denominator;
		}

		absError += error;
		count++;

	}
	::std::cout << "Done calculating\n";
	::std::cout << absError << " " << count <<"\n";
	//return relative average error
	return (double) absError/count;


}

