
#include "Satellite.h"
#include "ImagesCollection.h"
#include "OutputUtil.h"
#include <string>
#include <vector>
#pragma once
/*
Class Univers.
	- Classe principale de l'algorithme.
	- Son constructeur prend un chemin vers le fichier d'input en paramètre permettant le parsing.
	- start() démarre l'IA
	- makeOutput() créer le fichier de sortie
*/
class Univers
{
private:
	std::vector<Satellite> listeSatellites;
	std::vector<ImagesCollection> listeImagesCollection;
	int tours;	// Tours actuel
	int tMax;	// Nb maximum de tours
	//void writeFile(std::string path, std::string fileName); // Write a new file in the repertory

public:
	//(Cons/Des)tructeurs
	Univers(std::string pathFile);
	~Univers();

	//IA
	void start();		// Lancer l'algorithme
	void nextTours();	// Fin du tours : Recalcule les positions de tous les Satellites. 
	int BestSatelliteForThisImage(int x, int y,int t); //Retourne l'ID (le name) du satellite le plus proche pour une image. 
												 //		-> x et y point GPS de l'image
	
	std::vector<ImagesCollection> imagesCollectionCompatible(); //Retourne un tableau contenant toutes les collections d'images compatibles avec le tours actuel par rapport à leurs time ranges
	//Parse
	void parse(std::string);
	ImagesCollection objImageCollection;	//object for calling number of taken photos
	
	//void recordOutput(OutputUtil optUtil); // Enregistre dans le fichier de sortie une nouvelle ligne pour la prise d'une photo.
	//bool is_empty(std::ifstream& pFile);	// check file is empty or not
	//bool isFileExsisting(std::string path, std::string fileName);	// checks file already exsits or not in the path

	//Getters
	inline int getTours() { return tours; }
	inline int getToursMax() { return tMax; }
	inline int getToursRestant() { return tMax - tours; }
	inline std::vector<Satellite> getListeSatellites() { return listeSatellites; }
	inline Satellite getSatellite(int i) { return listeSatellites.at(i); }
	inline std::vector<ImagesCollection> getListeImagesCollection() { return listeImagesCollection; }
	inline ImagesCollection getImagesCollection(int i) { return listeImagesCollection.at(i); }
};

