#include<iostream>
#include<fstream>
#include <math.h>

#include "vpa_n.h"
bool vpa_n::VPA::UPCASTING = false;



#include "inversek2j.hpp" // function definition

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


	double WCE = 0.0;
	double tmp;

	double greal, gima;
	double axreal, axima;
	double diffreal, diffimg;
	
	while (!oracle.eof () && !axc.eof()) {
	
		oracle >> greal >> gima;
		axc >> axreal >> axima;
		diffreal =  (greal - axreal)  ;
		diffimg = (gima - axima);


		tmp = sqrt (  (diffreal*diffreal) + (diffimg*diffimg)  );
		//tmp = abs (good_v - axc_v);
		if (tmp > WCE) {
			WCE = tmp;
		}

	}
	return WCE;


}

