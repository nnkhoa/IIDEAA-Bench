/*
 * kinematics.cpp
 * 
 *  Created on: Sep. 10 2013
 *			Author: Amir Yazdanbakhsh <yazdanbakhsh@wisc.edu>
 */

#include <cmath>
#include "kinematics.hpp"
#include "vpa_n.h"

float l1 = 0.5 ;
float l2 = 0.5 ;

::vpa_n::VPAPrecision OP_5 = ::vpa_n::DOUBLE;
::vpa_n::VPAPrecision OP_4 = ::vpa_n::DOUBLE;
::vpa_n::VPAPrecision OP_3 = ::vpa_n::DOUBLE;
::vpa_n::VPAPrecision OP_2 = ::vpa_n::DOUBLE;
::vpa_n::VPAPrecision OP_1 = ::vpa_n::DOUBLE;
::vpa_n::VPAPrecision OP_0 = ::vpa_n::DOUBLE;
void forwardk2j(float theta1, float theta2, float* x, float* y) {
	*x =(double)( ::vpa_n::VPA(::vpa_n::VPA(l1 , OP_1)* ::vpa_n::VPA(cos(theta1), OP_1) , OP_0)+ ::vpa_n::VPA(::vpa_n::VPA(l2 , OP_2)* ::vpa_n::VPA(cos(theta1 + theta2), OP_2), OP_0)) ;
	*y =(double)( ::vpa_n::VPA(::vpa_n::VPA(l1 , OP_4)* ::vpa_n::VPA(sin(theta1), OP_4) , OP_3)+ ::vpa_n::VPA(::vpa_n::VPA(l2 , OP_5)* ::vpa_n::VPA(sin(theta1 + theta2), OP_5), OP_3)) ;
}

void inversek2j(float x, float y, float* theta1, float* theta2) {

	double dataIn[2];
	dataIn[0] = x;
	dataIn[1] = y;

	double dataOut[2];

//#pragma parrot(input, "inversek2j", [2]dataIn)

	*theta2 = (float)acos(((x * x) + (y * y) - (l1 * l1) - (l2 * l2))/(2 * l1 * l2));
	*theta1 = (float)asin((y * (l1 + l2 * cos(*theta2)) - x * l2 * sin(*theta2))/(x * x + y * y));

	dataOut[0] = (*theta1);
	dataOut[1] = (*theta2);

//#pragma parrot(output, "inversek2j", [2]<0.0; 2.0>dataOut)


	*theta1 = dataOut[0];
	*theta2 = dataOut[1];
}
