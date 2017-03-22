#include "OutputFormat.h"



OutputFormat::OutputFormat()
{

}

OutputFormat::OutputFormat(int lon, int lat, int tours, int satellite, int numberOfPhotos, std::string path, std::string fileName)
{
	int long;
	longitude= lon ;
	latitude = lat;
	this->tours = tours;
	this->satellite = satellite;
	this->numberOfPhotos = numberOfPhotos;
	this->path = path;
	this->fileName= fileName;
}


OutputFormat::~OutputFormat()
{
}
