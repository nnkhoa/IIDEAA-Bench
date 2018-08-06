#include "jpegloader.h"

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

	if((infile - fopen(filename.c_str(), "rb")) == NULL) {
		return NULL;
	}

	info.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = errorHandler;

	jpeg_create_decompress(&info);
	jpeg_stdio_src(&info, infile);
	jpeg_read_header(&info, TRUE);
	jpeg_start_decompress(&info);
	rowStride = info.output_width * info.output_components;
	if (info.out_color_components < 3) {
		jpeg_destroy_decompress(&info);
		fclose(infile);
		return NULL;
	}

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
