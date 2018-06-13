/*
 * kmeans.c
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


#include <stdio.h>
#include <string>
#include "rgbimage.h"
#include "segmentation.h"
#include <iostream>
#include <fstream>
#include <sstream>

int calculateKMeans(const char* inputImage, const char* outputImage) {
	RgbImage srcImage;
	Clusters clusters;

	initRgbImage(&srcImage);

	std::string inImageName  = inputImage;
	std::string outImageName = outputImage;

	if(loadRgbImage(inImageName.c_str(), &srcImage, 256) != 0) {
		return -1;
	}

	initClusters(&clusters, 6, 1);
	segmentImage(&srcImage, &clusters, 1);
	
	saveRgbImage(&srcImage, outImageName.c_str(), 255);


	freeRgbImage(&srcImage);
	freeClusters(&clusters);

	return 0;	
}

int main (int argc, const char* argv[]) {
	if(calculateKMeans(argv[1], argv[2]) != 0) {
		::std::cerr << "Error in calculating process\n";
		return 1;
	}
	return 0;
}

