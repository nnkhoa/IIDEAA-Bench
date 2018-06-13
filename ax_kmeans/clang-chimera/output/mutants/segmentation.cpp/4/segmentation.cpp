/*
 * segmentation.c
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


#include "segmentation.h"
#include <stdio.h>
#include <stdlib.h>

#include "vpa_n.h"
#include "fap.h"
#include "distance.h"

int initClusters(Clusters* clusters, int k, float scale) {
	int i;
	float x;

	clusters->centroids = (Centroid*)malloc(k * sizeof(Centroid));

	if (clusters == NULL) {
		printf("Warning: Oops! Cannot allocate memory for the clusters!\n");

		return -1;
	}

	clusters->k = k;
	for (i = 0; i < clusters->k; i ++) {
		x = (((float)rand())/RAND_MAX) * scale;
		clusters->centroids[i].r = x;

		x = (((float)rand())/RAND_MAX) * scale;
		clusters->centroids[i].g = x;

		x = (((float)rand())/RAND_MAX) * scale;
		clusters->centroids[i].b = x;

		clusters->centroids[i].n = 0;
	}


	return 0;
}

void freeClusters(Clusters* clusters) {
	if (clusters != NULL)
		free(clusters->centroids);
}

::vpa_n::VPAPrecision OP_5 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_4 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_3 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_2 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_1 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_0 = ::vpa_n::FLOAT;
void segmentImage(RgbImage* image, Clusters* clusters, int n) {
	int i;
	int x, y;
	int c;

	for (i = 0; i < n; ++i) {
		for (y = 0; y < image->h; y++) {
			for (x = 0; x < image->w; x++) {
				assignCluster(&image->pixels[y][x], clusters);
			}
		}

		/** Recenter */
		for (c  = 0; c < clusters->k; ++c) {
			clusters->centroids[c].r = 0.;
			clusters->centroids[c].g = 0.;
			clusters->centroids[c].b = 0.;
			clusters->centroids[c].n = 0;
		}
		for (y = 0; y < image->h; y++) {
			for (x = 0; x < image->w; x++) {
				clusters->centroids[image->pixels[y][x].cluster].r = (float)(::vpa_n::VPA(clusters->centroids[image->pixels[y][x].cluster].r, OP_0) + ::vpa_n::VPA(image->pixels[y][x].r, OP_0));
				clusters->centroids[image->pixels[y][x].cluster].g = (float)(::vpa_n::VPA(clusters->centroids[image->pixels[y][x].cluster].g, OP_1) + ::vpa_n::VPA(image->pixels[y][x].g, OP_1));
				clusters->centroids[image->pixels[y][x].cluster].b = (float)(::vpa_n::VPA(clusters->centroids[image->pixels[y][x].cluster].b, OP_2) + ::vpa_n::VPA(image->pixels[y][x].b, OP_2));
				clusters->centroids[image->pixels[y][x].cluster].n += 1;
			}
		}
		for (c  = 0; c < clusters->k; ++c) {
			if (clusters->centroids[c].n != 0) {
				clusters->centroids[c].r =(float)( ::vpa_n::VPA(clusters->centroids[c].r , OP_3)/ ::vpa_n::VPA(clusters->centroids[c].n, OP_3));
				clusters->centroids[c].g =(float)( ::vpa_n::VPA(clusters->centroids[c].g , OP_4)/ ::vpa_n::VPA(clusters->centroids[c].n, OP_4));
				clusters->centroids[c].b =(float)( ::vpa_n::VPA(clusters->centroids[c].b , OP_5)/ ::vpa_n::VPA(clusters->centroids[c].n, OP_5));
			}
		}
	}

	for (y = 0; y < image->h; y++) {
		for (x = 0; x < image->w; x++) {
			image->pixels[y][x].r = clusters->centroids[image->pixels[y][x].cluster].r;
			image->pixels[y][x].g = clusters->centroids[image->pixels[y][x].cluster].g;
			image->pixels[y][x].b = clusters->centroids[image->pixels[y][x].cluster].b;
		}
	}
}

