/*
 * fvec_dump.cpp
 *
 *  Created on: 27 févr. 2015
 *      Author: jfellus
 */


#include "Matrix.h"

std::string file;
std::string format = "txt";


void vector_sdiv_float(float* x, float f, uint n) {
	for(uint i = 0; i<n; i++) x[i]/=f;
}

float vector_n2_float(float* x, uint n) {
	float z = 0;
	for(uint i = 0; i<n; i++) z += x[i]*x[i];
	return sqrtf(z);
}



int main(int argc, char **argv) {
	if(argc<3) {
		DBG("Usage : " << argv[0] << " <in.fvec> <out.fvec>");
	}
	file = argv[1];

	Matrix X;
	X.read(file);
	for(uint i=0; i<X.height; i++) {
		vector_sdiv_float(&X[i*X.width], vector_n2_float(&X[i*X.width], X.width), X.width);
	}
	X.write(argv[2]);
}
