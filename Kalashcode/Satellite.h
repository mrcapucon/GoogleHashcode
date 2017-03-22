// Classe Satellite
// -> Représente un unique satellite et sa caméra dans l'univers
#include<iostream>
#include "OutputUtil.h"
#pragma once
class Satellite
{
private:
	//Satellite
	int name;				// Numéro

	int lattitude;			// Phi
	int longitude;			// Lambda
	int vitesse;			// V
	int currentTurn;		// T
	
	bool busy;				// True si le satelite doit prendre une photo et est donc pris
	int xphoto;				// x de la photo 
	int yphoto;				// y de la photo 			
	int tphoto;				// t ou doit etre pris la photo
	int counter;
	//Camera
	int vitesseCam;			// w
	int angle;				// d
	float xCam;				// dans l'intervalle [-d, d]
	float yCam;				// dans l'intervalle [-d, d]
	void writeFile(std::string path, std::string fileName); // Write a new file in the repertory


public:
	Satellite(int id, int phi, int lambda, int v, int w, int d); // Constructeur initialisateur.
	Satellite(const Satellite &sat);	//Constructeur par recopie				(Facultatif?)
	~Satellite();

	inline int getName() { return name; }; // Retourne l'identifiant du satellite
	inline int getLongitude() { return longitude; };				// Retourne la longitude du tours actuel
	inline int getLattitude() { return lattitude; };				// Retourne la lattitude du tours actuel
	inline int getVitesse() { return vitesse; };				// Retourne la vitesse du satellite
	inline int getCurrentTurn() { return currentTurn; };			// Retourne le n° du tours en cours
	inline int getBusy() { return busy; };			// Retourne le n° du tours en cours
	inline int getTphoto() { return tphoto; };


	int getNextLattitude();	//Retourne la Lattitude du satellite au tours t+1.
	int getNextLattitude(int t);
	int getNextLongitude();	//Retourne la Longitude du satellite au tours t+1.
	int getNextLongitude(int t);	//Retourne la Longitude du satellite au tours t+1.
	int getNextVelocity();	//Retourne la vitesse du satellite au tours t+1.

	int getXcam();
	int getYcam();
	void setNextTurn();
	void recordOutput(); // Enregistre dans le fichier de sortie une nouvelle ligne pour la prise d'une photo.
	bool is_empty(std::ifstream& pFile);	// check file is empty or not
	bool isFileExsisting(std::string path, std::string fileName);	// checks file already exsits or not in the path


	int isImageRange(int x, int y,int tmax);	//Retourne -1 si un point GPS (x,y) n'est pas visible par la caméra
												//Retourne le premier t en arcseconde pour lequel le point est visible sinon
	int whenShot(int x, int y);					//Retourne le premier t en arcseconde pour lequel le point est visible
												
	void giveAPhoto(int x, int y);

};

