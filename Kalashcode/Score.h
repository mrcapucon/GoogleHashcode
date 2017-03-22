#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Univers.h"
#include "ImagesCollection.h"
#include "Satellite.h"
#include "Utils.h"

int calculerScore(std::string, std::string);

// Fonction qui calcule le score en fonction du nom de fichier sans l'extension
// Par exemple, pour la collection forever_alone --> calculerScore("forever_alone") cherche forever_alone.in et forever_alone.out dans les ressources du projet
// et calcule le score. Pour l'instant dans les ressources, il faudra changer ça
int calculerScore(std::string filepathIN, std::string filepathOUT) {

	std::ifstream fichierIN;
	fichierIN.open(filepathIN);

	Univers u(filepathIN);

	std::ifstream fichierOUT;
	fichierOUT.open(filepathOUT);
	if (fichierOUT.is_open()) std::cout << "File " << filepathOUT << " loaded successfully..." << std::endl;
	else std::cout << "Error reading " << filepathOUT << std::endl;

	/*if (!fichierIN.is_open()) { std::cout << "FICHIERIN NOTOK" << std::endl;}
	else { std::cout << "FICHIERIN OK" << std::endl; }
	if (!fichierOUT.is_open()) { std::cout << "FICHIEROUT NOTOK" << std::endl;}
	else { std::cout << "FICHIEROUT OK" << std::endl; }*/

	std::vector<ImagesCollection> v = u.getListeImagesCollection();
	int score = 0, nbPhotos = 0, nbRestant = 0;
	std::string line;
	bool collectionScored = false, imageFound = false, timeRangeFound = false;

	// PARCOURS DE TOUTES LES COLLECTIONS
	for (int i = 0; i < v.size(); i++) {
		int k = v[i].getImages().size();
		int kk = v[i].getTimeRanges().size();
		//std::cout << "size of collection:\t" << k << std::endl;
		collectionScored = false;
		// PARCOURS DE TOUTES LES IMAGES
		int j = 0;
		while ((j < k) && !collectionScored) {
			imageFound = false;
			//std::cout << "Image a tester classe:\tlat: " << v[i].getImage(j)[0] << "\tlongi: " << v[i].getImage(j)[1] << std::endl;
			collectionScored = false;
			getline(fichierOUT, line);
			while (getline(fichierOUT, line) && !imageFound) {
				int lat, longi, t, id;
				std::string linePic = line;
				//std::cout << "ligne fichier a tester: " << linePic << std::endl;
				std::vector<std::string> varPic;
				split(linePic, ' ', varPic);
				lat = stoi(varPic[0]);
				longi = stoi(varPic[1]);
				t = stoi(varPic[2]);
				id = stoi(varPic[3]);
				//std::cout << "Image a tester fichier:\tlat: " << lat << "\tlongi: " << longi << std::endl;
				if (lat == v[i].getImage(j)[0] && longi == v[i].getImage(j)[1]) {
					int jj = 0;
					while ((jj < kk) && !imageFound) {
						if (t >= v[i].getTimeRange(jj)[0] && t <= v[i].getTimeRange(jj)[1]) {
							imageFound = true;
						}
						jj++;
					}

					//std::cout << "j:\t" << j+1 << std::endl;
					if ((j + 1) == k && imageFound) { collectionScored = true; }
				}
				//std::cout << "MATCH: " << imageFound << std::endl;
				varPic.clear();

				//std::cout << collectionScored << std::endl;
			}
			j++;
			//std::cout << "SORTIE DE WHILE" << std::endl;

			fichierOUT.clear();
			//if (!getline(fichierOUT, line)) 
			fichierOUT.seekg(0, std::ios_base::beg);
			//std::cout << "SCORED: " << collectionScored << std::endl;
			if (collectionScored)
				score += v[i].getScore();
			//std::cout << "SCORE: " << score << std::endl;


		}
	}

	return score;
}