#pragma once

#include "Satellite.h"
#include "ImagesCollection.h"
#include <string>
#include <vector>

void split(const std::string &s, char delim, std::vector<std::string> &elems);
int convLat(int a, int b, int c, char d);
int convLong(int a, int b, int c, char d);