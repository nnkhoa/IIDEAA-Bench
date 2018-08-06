/*
 * jpeg.c
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "datatype.h"
#include "jpegconfig.h"
#include "prototype.h"

#include "rgbimage.h"
#include "jpeglib.h"

#define OUT_BUFFER_SIZE 500000 // in bytes
int jpegConversion(const char* inputFileName, const char* outputFileName){
	UINT32 qualityFactor;
	UINT32 imageFormat;

	UINT8 *outputBuffer;
	FILE *fp;

	UINT8 *outputBufferPtr;


	qualityFactor = 1024;
	imageFormat = GRAY;

	// ::std::cout << "Fault Check - 1\n";
	RgbImage srcImage;
	initRgbImage(&srcImage);
	if (loadRgbImage(inputFileName, &srcImage) == 0) {
		printf("Error! Oops: Cannot load the input image!\n");
		return -1;
	}

	makeGrayscale(&srcImage);

	outputBuffer = (UINT8 *) malloc(OUT_BUFFER_SIZE * sizeof(UINT8));

	// ::std::cout << "Fault Check - 2\n";

	outputBufferPtr = outputBuffer;
	// ::std::cout << "Fault Check - 3\n";
	outputBufferPtr = encodeImage(
		&srcImage, outputBufferPtr, qualityFactor, imageFormat
	);


	freeRgbImage(&srcImage);

	fp = fopen(outputFileName, "wb");
	if (fp != NULL) {
		fwrite(outputBuffer, 1, outputBufferPtr - outputBuffer, fp);
		fclose(fp);
	}
	free(outputBuffer);
	return 0;
}

int main (int argc, const char* argv[]) {
	jpegConversion(argv[1], argv[2]);
	return 0;
}

