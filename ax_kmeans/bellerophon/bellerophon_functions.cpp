#include <iostream>
#include <string>
#include <math.h>

#include "vpa.h"
#include "kmeans.h"
#include "rgbimage.h"
//#include "fap.h"

// bool vpa_n::VPA::UPCASTING = false;

const char* inputPath = "/opt/ax_kmeans/test.data/input/10.rgb";
const char* axPath = "/opt/ax_kmeans/src/build/ax.rgb";
const char* oraclePath = "/opt/ax_kmeans/src/build/oracle.rgb";

double calDistance(RgbPixel p, RgbPixel q) {
	float r = 0.0;

	r = pow(p.r - q.r, 2) + pow(p.g - q.g, 2) + pow(p.b - q.b, 2);

	return sqrt(r);	
}

void doAxCompute() {
	if (calculateKMeans(inputPath, axPath) != 0) {
		::std::cerr << "Error Executing Approximate Version of the program\n";
		exit(-1);
	}
}

int loadImageFile(const char* imagePath, RgbImage *image) {
	if (loadRgbImage(imagePath, image, 256) != 0) {
		::std::cerr << "Error opening file!\n";
		exit(-1);
	}
	return 0;
}

extern "C" double BELLERO_getError() {
	//execute Ax computation
	doAxCompute();

	RgbImage oracleImage;
	RgbImage axImage;

	initRgbImage(&oracleImage);
	initRgbImage(&axImage);

	//load image
	//::std::cout << "Opening Oracle Image file...\n";
	loadImageFile(oraclePath, &oracleImage);

	//::std::cout << "Opening Ax Image file...\n";
	loadImageFile(axPath, &axImage);	
	
	//calculate distance
	double distance = 0.0;

	int imageWidth = oracleImage.w;
	int imageHeight = oracleImage.h;

	for(int i = 0; i < imageWidth; i++) {
		for (int j = 0; j < imageHeight; j++) {
			distance += calDistance(oracleImage.pixels[i][j], axImage.pixels[i][j]);
		}
	}
	//return MSE
	return (double)distance/(imageWidth * imageHeight);

}

extern vpa::FloatingPointPrecision OP_0, OP_1, OP_2, OP_3, OP_4, OP_5;

extern "C" double BELLERO_Reward()
{
	double rew = 0;

	//  MantType mant;
	int gradeMant[6];
	int gradeExp[6];

	gradeMant[0] = 54 - OP_0.mant_size;
	gradeMant[1] = 54 - OP_1.mant_size;
	gradeMant[2] = 54 - OP_2.mant_size;
	gradeMant[3] = 54 - OP_3.mant_size;
	gradeMant[4] = 54 - OP_4.mant_size;
	gradeMant[5] = 54 - OP_5.mant_size;
    
	gradeExp[0] = 11 - OP_0.exp_size;
	gradeExp[1] = 11 - OP_1.exp_size;
	gradeExp[2] = 11 - OP_2.exp_size;
	gradeExp[3] = 11 - OP_3.exp_size;
	gradeExp[4] = 11 - OP_4.exp_size;
	gradeExp[5] = 11 - OP_5.exp_size;
	
	for(int i = 0; i < 6; i++)
		rew+=gradeMant[i]*gradeMant[i]+gradeExp[i];
//printf("Reward: %g\n\n", rew);
	return rew;
}

//extern fap::FloatPrecTy OP_0, OP_1, OP_2, OP_3, OP_4, OP_5;
//
//extern "C" double BELLERO_Reward()
//{
//  double rew = 0;
//
////  MantType mant;
//  int grade[6];
//
//  grade[0] = 23 - OP_0.mant_size;
//  grade[1] = 23 - OP_1.mant_size;
//  grade[2] = 23 - OP_2.mant_size;
//  grade[3] = 23 - OP_3.mant_size;
//  grade[4] = 23 - OP_4.mant_size;
//  grade[5] = 23 - OP_5.mant_size;
//
//  rew = (double)2*grade[0] + 2*pow(grade[1],2) + 2*pow(grade[3],2) + 2*pow(grade[4],2) + 2*pow(grade[5],2);
////  FloatPrecTy prec = OP_1.getPrec();
//
////  cout << prec.mant_size;
//
//  return rew;
//}
