#pragma once 

#include <string>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <iostream>
extern "C" {
	#include "jpeglib.h"
}
struct JpegInfo{
	char* buffer;
	int height;
	int width;
};

JpegInfo* loadJpeg(::std::string filename);
