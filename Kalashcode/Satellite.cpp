#include <iostream>
#include "Satellite.h"
#include"cmath"
#include <fstream>
using namespace std;

/* *** Constructeurs/Destructeurs *** */
Satellite::Satellite(int id,  int lambda, int phi, int v, int w, int d)
{
	name = id;
	lattitude = phi;
	longitude = lambda;
	vitesse = v;
	currentTurn = 0;
	
	busy = false;
	xphoto = -1;
	yphoto = -1;
	tphoto = -1;

	vitesseCam = w;
	angle = d;
	xCam = 0;
	yCam = 0;
	counter = 0;
}


Satellite::Satellite(const Satellite & sat)
{
	name = sat.name;
	lattitude = sat.lattitude;
	longitude = sat.longitude;
	vitesse = sat.vitesse;
	currentTurn = sat.currentTurn;
	
	busy = sat.busy;
	xphoto = sat.xphoto;
	yphoto = sat.yphoto;
	tphoto = sat.tphoto;

	vitesseCam = sat.vitesseCam;
	angle = sat.angle;
	xCam = sat.xCam;
	yCam = sat.yCam;
}


Satellite::~Satellite()
{
}

/* *** Getteurs *** */


int Satellite::getNextLattitude()
{	// 90° = 90*3600
	if (((lattitude + vitesse) >= -90 * 3600) && ((lattitude + vitesse) < 90 * 3600))
	{
		return lattitude + vitesse;
	}
	else if ((lattitude + vitesse) >= 90 * 3600)
	{
	

		return 180 * 3600 - (lattitude + vitesse);
	}
	else if ((lattitude + vitesse) < -90 * 3600)
	{
		return -(180 * 3600) - (lattitude + vitesse);
	}
}

int Satellite::getNextLattitude(int t)
{
	if (((lattitude + vitesse*t) >= -90 * 3600) && ((lattitude + vitesse*t) < 90 * 3600))
	{
		return lattitude + vitesse*t;
	}
	else if ((lattitude + vitesse*t) >= 90 * 3600)
	{

		return 180 * 3600 - (lattitude + vitesse*t);
	}
	else if ((lattitude + vitesse*t) < -90 * 3600)
	{
		return -(180 * 3600) - (lattitude + vitesse*t);
	}
}

int Satellite::getNextLongitude()
{
	if (((lattitude + vitesse) >= -324000) && ((lattitude + vitesse) <= 324000))
	{
		return longitude - (15);
	}
	else if (((lattitude + vitesse) > 324000) || ((lattitude + vitesse) < -324000))
	{
		return -(180 * 3600) + (longitude - (15));
	}
}

int Satellite::getNextLongitude(int t)
{
	if (((lattitude + vitesse*t) >= -324000) && ((lattitude + vitesse*t) <= 324000))
	{
		int tt= longitude - (15 * t);
		if (tt < -648000) tt += 1296000;
		return tt;
	}
	else if (((lattitude + vitesse*t) > 324000) || ((lattitude + vitesse*t) < -324000))
	{
		int tt = -(180 * 3600) + (longitude - (15 * t));
		if (tt < -648000) tt += 1296000;
		return tt;
		
	}
}

int Satellite::getNextVelocity()
{
	if ((lattitude + vitesse) > -324000 && (lattitude + vitesse) < 324000)
	{
		return vitesse;
	}
	else
	{
		return -vitesse;
	}
}

int Satellite::getXcam()
{
	return xCam;
}

int Satellite::getYcam()
{
	return yCam;
}

void Satellite::setNextTurn()
{
	lattitude = getNextLattitude();
	longitude = getNextLongitude();
	vitesse = getNextVelocity();
	currentTurn++;
	if (busy) {
		if (sqrt(powf((xCam + getNextLongitude(tphoto - currentTurn) - xphoto), 2) + powf((yCam + getNextLattitude(tphoto - currentTurn) - yphoto), 2)) > vitesseCam) {
			float yt = vitesseCam*cos(atan((yphoto - getNextLattitude(tphoto - currentTurn) / xphoto - getNextLongitude(tphoto - currentTurn) - xphoto)));
			float xt = vitesseCam*sin(atan((yphoto - getNextLattitude(tphoto - currentTurn) / xphoto - getNextLongitude(tphoto - currentTurn) - xphoto)));
			if (yphoto - getNextLattitude(tphoto - currentTurn) >= yCam)
				yCam += yt;
			else
				yCam -= yt;
			if (xphoto - getNextLongitude(tphoto - currentTurn) >= xCam)
				xCam += xt;
			else
				xCam -= xt;


		}
		else {
			xCam = xphoto - longitude;
			yCam = yphoto - lattitude;
		}
		if (tphoto == currentTurn) {
			// PUT YOUR FUNCTION HEAR APOURV
			counter++;
			recordOutput();
						}
	}
	
}

void Satellite::recordOutput()
{
	while (counter > 0)
	{
		std::ofstream file("Out.txt");

		file.close();

		std::ifstream recordFile;
		recordFile.open("Out.txt");
		std::ofstream recordOpt;
		recordOpt.open("Out.txt");
		//if file is empty
		if (is_empty(recordFile))
		{
			recordOpt << tphoto << std::endl;
			if (tphoto > 0) {
				recordOpt << lattitude << " " << longitude << " " << this->currentTurn << " " << this;
				tphoto--;
			}

		}
		//if the file is not empty
		else
		{
			int c = recordFile.peek();
			if (c == EOF) {
				if (recordFile.eof())
				{
					recordOpt << tphoto << std::endl;
					if (tphoto > 0) {
						recordOpt << lattitude << " " << longitude << " " << this->currentTurn << " " << this;
						tphoto--;
					}
				}
			}
		}

		recordFile.close();
		recordOpt.close();

	}
}

//checks file is empty or not
bool Satellite::is_empty(std::ifstream & pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

//checks file exsists or not
bool Satellite::isFileExsisting(std::string path, std::string fileName)
{

	std::ifstream file(path + "/" + fileName);
	return file.good();

}

//writes a new file in the repository
void Satellite::writeFile(std::string path, std::string fileName)
{
	std::ofstream file(path + "/" + fileName);

	file.close();

}


// Retourne True, si le paramètre "Longitude" se situe dans le champs de vision global x de la caméra. 
int Satellite::isImageRange(int x, int y, int tmax)
{
	for (int t = 0; t < tmax-currentTurn; t++)
	{
		
		if (((getNextLongitude(t) - angle <= x) && (x <= getNextLongitude(t) + angle))		//  longitude - d < x < longitude + d 
			&& ((getNextLattitude(t) - angle <= y) && (y <= getNextLattitude(t) + angle))) { //  lattitude - d < y < lattitude + d 

			if (t*vitesseCam >= sqrt(2)*angle * 2) {

				return t;

			}
			else {

				if (t*vitesseCam >= sqrt(powf((x - xCam - getNextLongitude(t)), 2) + powf((y - yCam - getNextLattitude(t)), 2))) {


					return t;
				}

			}
		}
		
	}
	return -1;
}
int Satellite::whenShot(int x, int y)
{
	int t = 0;
	while (true)
	{

		if (((getNextLongitude(t) - angle <= x) && (x <= getNextLongitude(t) + angle))		//  longitude - d < x < longitude + d 
			&& ((getNextLattitude(t) - angle <= y) && (y <= getNextLattitude(t) + angle))) {  //  lattitude - d < y < lattitude + d 
			if (t*vitesseCam >= sqrt(2)*angle * 2) {

				return t;

			}
			else {
				if (t*vitesseCam >= sqrt(powf((x - xCam - getNextLongitude(t)), 2) + powf((y - yCam - getNextLattitude(t)), 2))) {
					return t;
				}


			}
		}
		t++;
	}
	return -1;
}

void Satellite::giveAPhoto(int x, int y)
{
	xphoto = x;
	busy = true;
	yphoto = y;
	tphoto = whenShot(x, y);

}
