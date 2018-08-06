#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <setjmp.h>

#include "vpa.h"
#include "jpeg.h"
#include "rgbimage.h"
extern "C" {
	#include "jpeglib.h"
}
// #include "jpegloader.h"
struct JpegInfo{
	char* buffer;
	int height;
	int width;
};

struct ErrorManager {
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};
typedef struct ErrorManager * my_error_ptr;

void errorHandler(j_common_ptr info) {
	my_error_ptr myerr = (my_error_ptr) info->err;
	(*info->err->output_message) (info);
	longjmp(myerr->setjmp_buffer, 1);
}

JpegInfo* loadJpeg(::std::string filename) {
	struct ErrorManager jerr;
	struct jpeg_decompress_struct info;
	FILE * infile;
	JSAMPARRAY buffer;
	int rowStride;

	if((infile = fopen(filename.c_str(), "rb")) == NULL) {
		::std::cerr << "NULL file\n";
		return NULL;
	}

	info.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = errorHandler;

	jpeg_create_decompress(&info);
	jpeg_stdio_src(&info, infile);
	jpeg_read_header(&info, TRUE);
	jpeg_start_decompress(&info);
	rowStride = info.output_width * info.output_components;
	
	int bufferSize = info.output_height * rowStride;
	unsigned char *imageBuffer = new unsigned char[bufferSize]();

	buffer = (*info.mem->alloc_sarray) ((j_common_ptr) &info, JPOOL_IMAGE, rowStride, 1);
	while (info.output_scanline < info.output_height) {
		jpeg_read_scanlines(&info, buffer, 1);
		memcpy(&imageBuffer[(info.output_scanline - 1) * rowStride], *buffer, rowStride);
	}
	jpeg_finish_decompress(&info);
	jpeg_destroy_decompress(&info);
	fclose(infile);

	JpegInfo *jpegInfo = new JpegInfo();
	jpegInfo->buffer = (char*)imageBuffer;
	jpegInfo->width = info.output_width;
	jpegInfo->height = info.output_height;

	return jpegInfo;
}
//#include "fap.h"

// bool vpa_n::VPA::UPCASTING = false;

const char* inputPath = "/opt/ax_jpeg/test.data/input/10.rgb";
const char* axPath = "/opt/ax_jpeg/src/build/ax.jpg";
const char* oraclePath = "/opt/ax_jpeg/src/build/oracle.jpg";


//double calDistance(RgbPixel p, RgbPixel q) {
//	float r = 0.0;
//
//	r = pow(p.r - q.r, 2) + pow(p.g - q.g, 2) + pow(p.b - q.b, 2);
//
//	return sqrt(r);	
//}

void doAxCompute() {
	::std::cout << "Do Ax Compute\n";
	if (jpegConversion(inputPath, axPath) != 0) {
		::std::cerr << "Error Executing Approximate Version of the program\n";
		exit(-1);
	}
	::std::cout << inputPath << " " << axPath << "\n";
}

void loadImageFile(const char* imagePath, JpegInfo **image) {
	::std::string pathString = imagePath;
	*image = loadJpeg(pathString);
	// std::cout << *image->width << "x" << *image->height << std::endl;
	if (image == NULL){
		::std::cout << "Cannot open file!\n";
		exit(-1);
	}
}

double calculateRMSE(JpegInfo *oracle, JpegInfo *ax){	
	int imageWidth = oracle->width;
	int imageHeight = oracle->height;
	double sumSquareError = 0;
	double MSE = 0;
	double diff = 0;
	for(int i = 0; i < imageWidth; i++) {
		for (int j = 0; j < imageHeight; j++) {
			diff = abs(oracle->buffer[i*imageWidth + j] - ax->buffer[i*imageWidth + j]);
			sumSquareError += pow(diff, 2);
		
		}
	}
	::std::cout << imageHeight << " " << imageWidth << "\n";
	return sqrt((double)sumSquareError/(imageWidth*imageHeight));
}

extern "C" double BELLERO_getError() {
	//execute Ax computation
	doAxCompute();

	JpegInfo *oracleImage = new JpegInfo();
	JpegInfo *axImage = new JpegInfo();


	//load image
	::std::cout << "Opening Oracle Image file...\n";
	loadImageFile(oraclePath, &oracleImage);

	::std::cout << "Opening Ax Image file...\n";
	loadImageFile(axPath, &axImage);	
	

	//return MSE
	return calculateRMSE(oracleImage, axImage);

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
