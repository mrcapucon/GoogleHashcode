#include "ImagesCollection.h"

#include <vector>
#include <array>


ImagesCollection::ImagesCollection(int score, std::vector<std::array<int,2>> images, std::vector<std::array<int,2>> timeRanges, int nbImg, int nbTimeRanges)
	: score(score), images(images), timeRanges(timeRanges), nbImg(nbImg), nbTimeRanges(nbTimeRanges)
{ }

ImagesCollection::ImagesCollection(const ImagesCollection & ic)
{
	score = ic.score;
	images = ic.images;
	timeRanges = ic.timeRanges;
	nbImg = ic.nbImg;
	nbTimeRanges = ic.nbTimeRanges;

}
ImagesCollection::ImagesCollection()
{}

ImagesCollection::~ImagesCollection()
{
	////freespace des images
	//for (int i = 0; i < nbimg; i++)
	//	delete[] images[i];
	//delete[] images;

	////freespace des timeranges
	//for (int i = 0; i < nbtimeranges; i++)
	//	delete[] timeranges[i];
	//delete[] timeranges;
}

std::vector<std::array<int,2>> ImagesCollection::getImages()
{
	return images;
}

std::array<int,2> ImagesCollection::getImage(int i)
{
	return images.at(i);
}

int ImagesCollection::getScore()
{
	return score;
}

std::vector<std::array<int,2>> ImagesCollection::getTimeRanges()
{
	return timeRanges;
}

std::array<int,2> ImagesCollection::getTimeRange(int i)
{
	return timeRanges.at(i);
}

int ImagesCollection::getNbImg()
{
	return nbImg;
}

int ImagesCollection::getNbTimeRanges()
{
	return nbTimeRanges;
}
