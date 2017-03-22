#include "Univers.h"

#include "Utils.h" 
#include "Satellite.h"
#include "ImagesCollection.h"

#include <fstream>
#include <iostream>
#include <string>

#include <sstream>
#include <vector>

Univers::Univers(std::string filePath)
{
	parse(filePath);
	
} 

Univers::~Univers()
{
}

void Univers::start()
{	
	int timax = tMax, compteur=0;


	while (tours<tMax)
	{
		std::cout << "##### Tour " << tours << "/" << tMax << " #####" << std::endl;
		//1. Obtention de toutes les collections d'images dont leurs times ranges est compatible avec le tour actuel.
		std::cout << "Recuperation des images disponibles pour ce tour... : ";
		std::vector<ImagesCollection> imagesCollectionsOk = this->imagesCollectionCompatible();
		std::cout << "Ok !" << std::endl << std::endl;

		//2. Pour chaque image compatible...
		for each (ImagesCollection ic in imagesCollectionsOk)
		{
			//std::cout << "Chargement d'une nouvelle collection..." << std::endl;
			for each (std::array<int,2> image in ic.getImages())
			{
				//std::cout << "Cherche le meilleur satellite pour (" << image[0] << "," << image[1] << ") ... : ";
				for (int i = 0; i < ic.getNbTimeRanges() - 1; i++) {
					if ((tours >= ic.getTimeRanges().at(i)[0]) && (tours <=ic.getTimeRanges().at(i)[1]))
						timax = ic.getTimeRanges().at(i)[1];
				}
				if (BestSatelliteForThisImage(image[1], image[0], timax) > -1)
					compteur++;
				
			}
		}
		std::cout << "Nous avons trouvé " << compteur << " satellites disponibles" << std::endl;
		compteur = 0;
		//3. 

		//4. 

		// Fin du tours
		this->nextTours();
	}
}

void Univers::nextTours()
{
	for each (Satellite lc in this->listeSatellites)
	{
		lc.setNextTurn();
	}
	tours++;
}

int Univers::BestSatelliteForThisImage(int x, int y,int timax)
{
	int toursMinimum = timax;	//Dernier Nombre de tours minimum trouvé.
	int toursTampon;					//Tampon. Stock le tours du satellite en cours d'étude.
	int satNameMinimum = -1;				//Satellite avec un minimum de tours correspondant trouvé.


	//std::cout << "Bienvenue dans BSFTI pour " << x << "," << y << " tMin:" << toursMinimum <<  std::endl;
	for (auto &sat : listeSatellites) //RQ : Syntaxe "for each" depuis C++11 only
	{
		toursTampon = sat.isImageRange(x, y, timax);
		//std::cout << toursTampon << std::endl;
		if (toursTampon > -1 && toursTampon < toursMinimum ) //Si Satellite courant peut capter cette image ET dans un tours plus petit que le précédent trouvé ET il n'est pas dans l'état occupé.
		{
			if (!sat.getBusy()) {
				sat.giveAPhoto(x, y);
				satNameMinimum = sat.getName();
				toursMinimum = toursTampon;		//MaJ du meilleur nombre de tours Minimum
			}
			else {
				if (toursTampon < sat.getTphoto()) {
					sat.giveAPhoto(x, y);
					satNameMinimum = sat.getName();
					toursMinimum = toursTampon;
				}
			}

		}
	}

	return satNameMinimum;
}

std::vector<ImagesCollection> Univers::imagesCollectionCompatible()
{
	std::vector<ImagesCollection> ImagesCollectionsOK; // Liste des ImagesCollections compatible avec le tours actuelle (Le TimeRange est Valide)

	for (auto &ic : this->listeImagesCollection) //RQ : Syntaxe "for each" depuis C++11 only
	{
		if (ic.isInTimeRanges(tours))	//Si le tour actuel est compatible avec le timeRanges de la collection
		{
			ImagesCollectionsOK.push_back(ic);
		}
	}

	return ImagesCollectionsOK;
}

void Univers::parse(std::string filepath)
{
	std::ifstream fichier;
	fichier.open(filepath);
	if (fichier.is_open()) {
		std::cout << "File " << filepath << " loaded successfully..." << std::endl;

		// VARIABLES LOCALES
		std::string line;
		int nbSatellite, currentSatellite = 1, phi, lambda, v, w, d,
			currentImageCollection = 1, nbImageCollections,
			score, nbImage, nbTimeRange,
			currentImage = 1, lat, longi,
			currentTimeRange = 1, begin, end;
		bool isNMode = true,
			isNbSatelliteMode = false, isSatelliteDescriptionMode = false,
			isNbImagesCollectionsMode = false, isImageCollectionsDescriptionMode = false,
			isImageDescriptionMode = false,
			isTimeRangeDescriptionMode = false;
		std::array<int,2> image;
		std::array<int,2> timeRange;
		std::vector<std::array<int,2>> images, timeRanges;

		// PARSING
		while (getline(fichier, line)) {

			// fini
			if (isNMode) {
				// Traitement
				tMax = stoi(line);
				// Changement de mode
				isNMode = false;
				isNbSatelliteMode = true;
			}

			// fini
			else if (isNbSatelliteMode) {
				// Traitement
				nbSatellite = stoi(line);
				// Changement de mode
				isNbSatelliteMode = false;
				isSatelliteDescriptionMode = true;
			}

			else if (isSatelliteDescriptionMode) {
				// Traitement
				if (currentSatellite <= nbSatellite) {
					int lambda, phi, v, w, d;
					std::string lineSat = line;
					std::vector<std::string> varSat;
					split(lineSat, ' ', varSat);
					lambda = stoi(varSat[0]);
					phi = stoi(varSat[1]);
					v = stoi(varSat[2]);
					w = stoi(varSat[3]);
					d = stoi(varSat[4]);
					
					listeSatellites.push_back(Satellite(currentSatellite-1, phi, lambda, v, w, d));
					
					// Changement de mode
					if (currentSatellite == nbSatellite) {
						isSatelliteDescriptionMode = false;
						isNbImagesCollectionsMode = true;
					}
					currentSatellite++;
				}
				// Changement de mode
				else {
					isSatelliteDescriptionMode = false;
					isNbImagesCollectionsMode = true;
				}
			}

			else if (isNbImagesCollectionsMode) {
				// Traitement
				nbImageCollections = stoi(line);
				// Changement de mode
				isNbImagesCollectionsMode = false;
				isImageCollectionsDescriptionMode = true;
			}

			else if (isImageCollectionsDescriptionMode) {
				// Traitement
				if (currentImageCollection <= nbImageCollections) {
					std::string lineCollection = line;
					std::vector<std::string> varCollection;
					split(lineCollection, ' ', varCollection);
					score = stoi(varCollection[0]);
					nbImage = stoi(varCollection[1]);
					nbTimeRange = stoi(varCollection[2]);
					currentImage = 1;
					currentTimeRange = 1;
					isImageDescriptionMode = true;
					isImageCollectionsDescriptionMode = false;
					// Changement de mode
					if (currentImageCollection == nbImageCollections){
						isImageCollectionsDescriptionMode = false;
						}	
					currentImageCollection++;
				}
				// Changement de mode
				else {
					isImageCollectionsDescriptionMode = false;
				}
			}

			else if (isImageDescriptionMode) {
				if (currentImage <= nbImage) {

					std::string lineImage = line;
					std::vector<std::string> varImage;
					split(lineImage, ' ', varImage);
					lat = stoi(varImage[0]);
					longi = stoi(varImage[1]);

					image[0]=lat;
					image[1]=longi;
					images.push_back(image);
					//image.clear();
					if (currentImage == nbImage) {
					
						isImageDescriptionMode = false;
						isTimeRangeDescriptionMode = true;
					}
					currentImage++;
				}
				// Changement de mode
				else {
					isImageDescriptionMode = false;
					isTimeRangeDescriptionMode = true;
				}
			}

			else if (isTimeRangeDescriptionMode) {
				if (currentTimeRange <= nbTimeRange) {

					std::string lineTimeRange = line;
					std::vector<std::string> varTimeRange;
					split(lineTimeRange, ' ', varTimeRange);
					begin = stoi(varTimeRange[0]);
					end = stoi(varTimeRange[1]);
					
					timeRange[0] = begin;
					timeRange[1] = end;
					timeRanges.push_back(timeRange);

					//timeRange.clear();
					
					if (currentTimeRange == nbTimeRange) {
						listeImagesCollection.push_back(ImagesCollection(score, images, timeRanges, nbImage, nbTimeRange));
						timeRanges.clear();
						images.clear();
						isImageCollectionsDescriptionMode = true;
						isTimeRangeDescriptionMode = false;
					}
					currentTimeRange++;
				}
				else {
					listeImagesCollection.push_back(ImagesCollection(score, images, timeRanges, nbImage, nbTimeRange));
					timeRanges.clear();
					images.clear();
					isImageCollectionsDescriptionMode = true;
					isTimeRangeDescriptionMode = false;
				}
			}

		}
		std::cout << "Nous avons charge " << listeSatellites.size() << "satellites" << std::endl;
		std::cout << "Nous avons charge " << listeImagesCollection.size() << "collections d'images" << std::endl;
	}
	else {
		std::cout << "Can't load file " << filepath << std::endl;
	}

}

/*
//checks file is empty or not
bool Univers::is_empty(std::ifstream & pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

//checks file exsists or not
bool Univers::isFileExsisting(std::string path, std::string fileName) 
{
		
	std::ifstream file(path + "/" + fileName);
	return file.good();
	
}

//void Univers::recordOutput(OutputUtil optUtil)
{
	int numberOfPhotos = objImageCollection.getNbImg();
	if ( !isFileExsisting(optUtil.path, optUtil.fileName) ){	
			writeFile(optUtil.path, optUtil.fileName);
		}
	std::string outputFilePath = optUtil.path + "/" + optUtil.fileName;
	std::ifstream recordFile;
	recordFile.open(outputFilePath);
	std::ofstream recordOpt;
	recordOpt.open(outputFilePath);
	//if file is empty
	if (is_empty(recordFile))	
	{
		if (tMax == tours)
		{
			recordOpt << numberOfPhotos << std::endl;
			if (numberOfPhotos > 0) {
				recordOpt << optUtil.latitude << " " << optUtil.longitude << " " << optUtil.tours << " " << optUtil.satellite;
				numberOfPhotos--;
			}

		}
	}
	//if the file is not empty
	else
	{
		int c = recordFile.peek();
		if (c == EOF) {
			if (recordFile.eof())
			{
				if (tMax == tours)
				{
					recordOpt << numberOfPhotos << std::endl;
					if (numberOfPhotos > 0) {
						recordOpt << optUtil.latitude << " " << optUtil.longitude << " " << optUtil.tours << " " << optUtil.satellite;
						numberOfPhotos--;
					}

				}
			}
		}
	}
	
	recordFile.close();
	recordOpt.close();
}

//writes a new file in the repository
//void Univers::writeFile(std::string path,std::string fileName)
{ 
	std::ofstream file(path + "/" + fileName);
	
	file.close();

}
*/

