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
	if(argc<=1) throw std::runtime_error(TOSTRING("Usage : " << argv[0] << " [-f format] file"));
	if(!strcmp(argv[1], "-f")) {
		if(argc<=3) throw std::runtime_error(TOSTRING("Usage : " << argv[0] << " [-f format] file"));
		format = argv[2];
		file = argv[3];
	} else file = argv[1];

	Matrix X;
	X.read(file);

	std::cout << X.height << "x" << X.width << "\n";

	getc(stdin);

	if(format=="txt") {
		for(size_t i = 0; i<X.height; i++) {
			for(size_t j=0; j<X.width; j++) {
				std::cout << X(i,j) << " ";
			}
			std::cout << "\n";
		}
	} else if(format=="html") {
		std::cout << "<table>";
		for(size_t i = 0; i<X.height; i++) {
			std::cout << "<tr>";
			for(size_t j=0; j<X.width; j++) {
				std::cout << "<td>" << X(i,j) << "</td>";
			}
			std::cout << "</tr>\n";
		}
		std::cout << "</table>";
	} else if(format=="dims") {
		std::cout << X.height << " " << X.width << "\n";
	}
}


int main2(int argc, char **argv) {
	file = argv[1];

	int nbrows = 0;

	FILE* f = fopen(file.c_str(), "r");
	while(!feof(f)) {
		if(fgetc(f)=='\n') nbrows++;
	}
	fclose(f);

	std::cout << "NB ROWS ARE " << nbrows << "\n";

	Matrix X(nbrows, 1);
	f = fopen(file.c_str(), "r");
	int i=0;
	while(!feof(f)) {
		float x;
		fscanf(f, "%f", &x);
		X[i++] = x;
	}
	std::cout << "READ " << i << " rows\n";
	fclose(f);
	X.dump();
	X.write(argv[2]);
}
