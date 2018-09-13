/*
 * fft.cpp
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */

#include "tritri.hpp"

#include <fstream>
#include <iostream>
#include <map>

#include <time.h>       /* time */

#include <boost/algorithm/string/regex.hpp>


void jMeint(const char* inputData, const char* output) {
	int i;
	int x;
	int n;

	std::cout.precision(8);

	std::string inputFilename = inputData;
	std::string outputFilename = output;


	// prepare the output file for writting the theta values
	std::ofstream outputFileHandler;
	outputFileHandler.open(outputFilename);
	outputFileHandler.precision(5);

	// prepare the input file for reading the theta data
	std::ifstream inputFileHandler (inputFilename, std::ifstream::in);

	// first line defins the number of enteries
	inputFileHandler >> n;

	// create the directory for storing data
	float* xyz = (float*)malloc(n * 6 * 3 * sizeof (float)) ;
	if(xyz == NULL)
	{
		std::cout << "cannot allocate memory for the triangle coordinates!" << std::endl;
		exit(-1);
	}

	i = 0;
	while (i < n)
	{
		float a[18];
		inputFileHandler >> 	a[0] 	>> 	a[1] 	>> 	a[2] 	>> a[3] 	>> a[4] 		>> a[5] >>
						a[6]	>>	a[7]	>> 	a[8]	>> a[9]		>> a[10]		>> a[11] >>
						a[12]	>> 	a[13] 	>> 	a[14] 	>> a[15] 	>> a[16]	 	>> a[17];
		for(int j = 0 ; j < 18; j++)
		{
			xyz[i * 18 + j] = a[j];
		}
		i++;
	}

	int totalCount = 0 ;

	//double output = 0.0;


	for(i = 0 ; i < (n * 6 * 3); i += 6 * 3)
	{

		double dataIn[18];
		double dataOut[2];
		dataIn[0] 	= xyz[i + 0];
		dataIn[1] 	= xyz[i + 1];
		dataIn[2] 	= xyz[i + 2];
		dataIn[3] 	= xyz[i + 3];
		dataIn[4] 	= xyz[i + 4];
		dataIn[5] 	= xyz[i + 5];
		dataIn[6] 	= xyz[i + 6];
		dataIn[7] 	= xyz[i + 7];
		dataIn[8] 	= xyz[i + 8];

		dataIn[9]  	= xyz[i + 9];
		dataIn[10] 	= xyz[i + 10];
		dataIn[11] 	= xyz[i + 11];
		dataIn[12] 	= xyz[i + 12];
		dataIn[13] 	= xyz[i + 13];
		dataIn[14] 	= xyz[i + 14];
		dataIn[15] 	= xyz[i + 15];
		dataIn[16] 	= xyz[i + 16];
		dataIn[17] 	= xyz[i + 17];
		


		x = tri_tri_intersect(
				xyz + i + 0 * 3, xyz + i + 1 * 3, xyz + i + 2 * 3,
				xyz + i + 3 * 3, xyz + i + 4 * 3, xyz + i + 5 * 3);

		if(x == 0)
		{
			dataOut[0] = 0.2;
			dataOut[1] = 0.8;
		}
		else
		{
			dataOut[0] = 0.8;
			dataOut[1] = 0.2;
		}


		if(dataOut[0] < dataOut[1])
			x = 0;
		else
			x = 1;

		outputFileHandler << x << std::endl;
	}


	outputFileHandler.close();
	inputFileHandler.close();

	free(xyz) ;
	xyz = NULL ;

}

int main(int argc, char* argv[]) {
	jMeint(argv[1], argv[2]);
	return 0;
}
