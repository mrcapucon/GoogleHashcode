#include "Utils.h"
#include "Satellite.h"
#include "ImagesCollection.h"

#include <fstream>
#include <iostream>
#include <string>

#include <sstream>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

// Fonction servant à convertir en lattitude. Ex: 48°51'29''N -> lat=[175889]
int convLat(int a, int b, int c, char d) {
	int phi;
	if (d == 'N') {
		phi = 3600 * a + 60 * b + c;
	}
	else if (d == 'S') {
		phi = 3600 * (-a) + 60 * (-b) + c;
	}
	else {
		std::cout << "Latitude coordinate must be represent by N or S and not something else.";
	}
	return phi;
}

// Fonction servant à convertir en longitude. Ex: 2°17'40''E -> lat=[8260]
int convLong(int a, int b, int c, char d) {
	int lambda;
	if (d == 'E') {
		lambda = 3600 * a + 60 * b + c;
	}
	else if (d == 'W') {
		lambda = 3600 * (-a) + 60 * (-b) + c;
	}
	else {
		std::cout << "Longitude coordinate must be represent by E or W and not something else.";
	}
	return lambda;
}