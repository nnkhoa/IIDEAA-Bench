// #include <iostream>
// #include <stdlib>
// #include <fstream>
// #include <time.h>
// #include <iomanip>
// #include <string>
// 
// #include "kinematics.hpp"
// #include <boost/math/special_fucntions/fpclassify.hpp>
// 
// #define PI 3.141592653589
// 
void doWork(const char* inputPath, const char* outputPath);
//{
//	int n;
//
//	std::string inputFileName = inputPath;
//	std::string outputFileName = outputPath;
//
//	std::ofstream outputFileHandler;
//	outputFileHandler.open(outputFileName);
//
//	std::ifstream inputFileHandler(inputFilename, std::ifstream::in);
//	
//	inputFileHandler >> n;
//
//	float* t1t2xy = (float*)malloc(n * 2 * 2 * sizeof(float));
//
//	if(t1t2xy == NULL){
//		std::cerr << "# Cannot allocate memory for the coordinates an angles!" << std::endl;
//		return -1;
//	}
//
//	srand(time(NULL));
//
//	int curr_index1 = 0;
//	for(int i = 0; i < n * 2 * 2; i += 2 * 2){
//		float theta1, theta2;
//		inputFileHandler >> theta1 >> theta2;
//
//		t1t2xy[i] = theta1;
//		t1t2xy[i + 1] = theta2;
//
//		forwardk2j(t1t2xy[i + 0], t1t2xy[i + 1], t1t2xy + (i + 2), t1t2xy + (t + 3));
//	}
//
//	for(int i = 0; i < n * 2 * 2; i += 2 * 2){
//		inversek2j(t1t2xy[i + 2], t1t2xy[i + 3], t1t2xy + (i + 0), t1t2xy + (i + 1));
//	}
//
//	for(int i = 0; i < n * 2 * 2; i += 2 * 2){
//		outputFileHandler << t1t2xy[i + 0] << "\t" << t1t2xy[i + 1] << "\n";
//	}
//
//	inputFileHandler.close();
//	outputFileHandler.close();
//	free(t12xy);
//	t1t2xy = NULL;
//}
