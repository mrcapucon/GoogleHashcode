#include "OutputUtil.h"


OutputUtil::OutputUtil()
{
}

OutputUtil::OutputUtil(int lon, int lat, int tours, int satellite, std::string path, std::string fileName)
{
	longitude = lon;
	latitude = lat;
	this->tours = tours;
	this->satellite = satellite;
	this->path = path;
	this->fileName = fileName;

}


OutputUtil::~OutputUtil()
{
}
