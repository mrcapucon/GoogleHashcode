
#include <iostream>
#include <string>
#pragma once

//Class for generating output file
class OutputFormat
{
public:
	int longitude;
	int latitude;
	int tours;
	int satellite;
	int numberOfPhotos;
	std::string path;
	std::string fileName;

	OutputFormat();
	OutputFormat(int lon, int lat, int tours, int satellite, int numberOfPhotos, std::string path, std::string fileName);
	~OutputFormat();

};

