/*
 * distance.c
 * 
 * Created on: Sep 9, 2013
 * 			Author: Amir Yazdanbakhsh <a.yazdanbakhsh@gatech.edu>
 */


#include "distance.h"
#include "vpa_n.h"
#include <math.h>
#include <map>

int count = 0;
#define MAX_COUNT 1200000

::vpa_n::VPAPrecision OP_11 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_10 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_9 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_8 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_7 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_6 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_5 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_4 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_3 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_2 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_1 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_0 = ::vpa_n::FLOAT;
float euclideanDistance(RgbPixel* p, Centroid* c1) {
	float r;

	r = 0;
	double r_tmp;
	
	double dataIn[6];
	dataIn[0] = p->r;
	dataIn[1] = p->g;
	dataIn[2] = p->b;
	dataIn[3] = c1->r;
	dataIn[4] = c1->g;
	dataIn[5] = c1->b;

#pragma parrot(input, "kmeans", [6]dataIn)

	r = (float)(::vpa_n::VPA(r, OP_0) + ::vpa_n::VPA(::vpa_n::VPA((::vpa_n::VPA(p->r , OP_2)- ::vpa_n::VPA(c1->r, OP_2)) , OP_1)* ::vpa_n::VPA((::vpa_n::VPA(p->r , OP_3)- ::vpa_n::VPA(c1->r, OP_3)), OP_1), OP_0));
	r = (float)(::vpa_n::VPA(r, OP_4) + ::vpa_n::VPA(::vpa_n::VPA((::vpa_n::VPA(p->g , OP_6)- ::vpa_n::VPA(c1->g, OP_6)) , OP_5)* ::vpa_n::VPA((::vpa_n::VPA(p->g , OP_7)- ::vpa_n::VPA(c1->g, OP_7)), OP_5), OP_4));
	r = (float)(::vpa_n::VPA(r, OP_8) + ::vpa_n::VPA(::vpa_n::VPA((::vpa_n::VPA(p->b , OP_10)- ::vpa_n::VPA(c1->b, OP_10)) , OP_9)* ::vpa_n::VPA((::vpa_n::VPA(p->b , OP_11)- ::vpa_n::VPA(c1->b, OP_11)), OP_9), OP_8));

	r_tmp = sqrt(r);

#pragma parrot(output, "kmeans", <0.0; 1.0>r_tmp)

	return r_tmp;
}

int pickCluster(RgbPixel* p, Centroid* c1) {
	float d1;

	d1 = euclideanDistance(p, c1);

	if (p->distance <= d1)
		return 0;

	return 1;
}

void assignCluster(RgbPixel* p, Clusters* clusters) {
	int i = 0;

	float d;
	d = euclideanDistance(p, &clusters->centroids[i]);
	p->distance = d;

	for(i = 1; i < clusters->k; ++i) {
		d = euclideanDistance(p, &clusters->centroids[i]);
		if (d < p->distance) {
			p->cluster = i;
			p->distance = d;
		}
	}
}

