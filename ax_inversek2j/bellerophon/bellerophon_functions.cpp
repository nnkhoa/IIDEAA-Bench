#include<iostream>
#include<fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "vpa.h"
// bool vpa::VPA::UPCASTING = false;



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
	
	//::std::cout << "Calculating Error: \n";	
	while (!oracle.eof () && !axc.eof()) {
		//::std::cout << count << "\n";	
		oracle >> oValue0 >> oValue1;
		axc >> axValue0 >> axValue1;
		
		//::std::cout << oValue0 << " " << oValue1 << "\n";
		
		//check if any value is NaN
		if (oValue0.compare("nan") == 0 || oValue1.compare("nan") == 0 || axValue0.compare("nan") == 0 || axValue1.compare("nan") == 0) {
		//	::std::cout << "NaN\n";
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
	//::std::cout << "Done calculating\n";
	//::std::cout << absError << " " << count <<"\n";
	//return relative average error
	return (double) absError/count;
}

extern vpa::FloatingPointPrecision OP_0, OP_1, OP_2, OP_3, OP_4, OP_5;

extern "C" double BELLERO_Reward()
{
	double rew = 0;

	//  MantType mant;
	int gradeMant[6];
	int gradeExp[6];

	gradeMant[0] = 53 - OP_0.mant_size;
	gradeMant[1] = 53 - OP_1.mant_size;
	gradeMant[2] = 53 - OP_2.mant_size;
	gradeMant[3] = 53 - OP_3.mant_size;
	gradeMant[4] = 53 - OP_4.mant_size;
	gradeMant[5] = 53 - OP_5.mant_size;
    
	gradeExp[0] = 11 - OP_0.exp_size;
	gradeExp[1] = 11 - OP_1.exp_size;
	gradeExp[2] = 11 - OP_2.exp_size;
	gradeExp[3] = 11 - OP_3.exp_size;
	gradeExp[4] = 11 - OP_4.exp_size;
	gradeExp[5] = 11 - OP_5.exp_size;
	
	for(int i = 0; i < 6; i++)
		rew+=gradeMant[i]+gradeExp[i];
//printf("Reward: %g\n\n", rew);
	return rew;
}

