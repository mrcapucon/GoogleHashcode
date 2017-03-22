#include <iostream>
#include<string>
#pragma once
class OutputUtil
{
public:
	int longitude;	//longitude of photo taken by satellite
	int latitude;	//latitude of photo taken by satellite
	int tours;	//number of tours done by satellite when photo was taken 
	int satellite;	//number of satellite which takes the photo
	std::string path;	//path where ouput file to be written
	std::string fileName;	// name of the output file
	OutputUtil();
	//parameterised constructor for getting output values
	OutputUtil(int lon,int lat,int tours,int satellite, std::string path,std::string fileName);	
	~OutputUtil();
};

