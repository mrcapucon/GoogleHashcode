#pragma once

#include <vector>
#include <array>
/*
Classe ImagesCollection:
	Modélise une collection d'image.
	- A un score, une liste d'images, et une liste de créneau.
*/
class ImagesCollection
{
private:
	std::vector<std::array<int,2>> images;
	std::vector<std::array<int,2>> timeRanges;
	//int **images;	
	int score;			// V
	//int **timeRanges;	// R

	int nbImg;
	int nbTimeRanges;

public:
	ImagesCollection(int score, std::vector<std::array<int,2>> images, std::vector<std::array<int, 2>> timeRanges, int nbImg, int nbTimeRanges);
	ImagesCollection(const ImagesCollection &ic);
	ImagesCollection();
	~ImagesCollection();

	std::vector<std::array<int, 2>> getImages();
	std::array<int, 2> getImage(int i);
	int getScore();
	std::vector<std::array<int, 2>> getTimeRanges();
	std::array<int, 2> getTimeRange(int i);
	int getNbImg();
	int getNbTimeRanges();

	// Vérifie que les images peuvent être prisent à un tours passé en paramètre.
	inline bool isInTimeRanges(int tours)
	{
		for (int i = 0; i < nbTimeRanges ;i++)
		{
			if ((tours >= timeRanges.at(i)[0]) && (tours <= timeRanges.at(i)[1]))
				return true;
		}
		return false;
	}
};

