/*
 * fvec_dump.cpp
 *
 *  Created on: 27 févr. 2015
 *      Author: jfellus
 */


#include "Matrix.h"

std::string file;
std::string format = "txt";

int main(int argc, char **argv) {
	if(argc<=1) throw std::runtime_error(TOSTRING("Usage : " << argv[0] << " <file> <indices_subset_file> <outfile>"));
	file = argv[1];

	Matrix X;
	X.read(file);

	std::cout << X.height << "x" << X.width << "\n";

	int nbrows = 0;

	FILE* f = fopen(argv[2], "r");
	while(!feof(f)) {
		if(fgetc(f)=='\n') nbrows++;
	}
	fclose(f);

	Matrix Y(nbrows, X.width);
	std::cout << Y.height << "x" << Y.width << "\n";

	f = fopen(argv[2], "r");
	int i=0;
	while(!feof(f)) {
		int ind; fscanf(f, "%u", &ind);
		ind--;
		memcpy(&Y[X.width*(i++)],&X[X.width*ind],sizeof(float)*X.width);
		if(i==nbrows) break;
	}
	fclose(f);

	Y.write(argv[3]);
	std::cout << "ok\n";
}

