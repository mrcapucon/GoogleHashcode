#pragma once
#include "Satellite.h"
class Simulation
{
private :
	int nbSat;
	Satellite listSat[50];

public:
	Simulation();
	Simulation(int nb);

	Simulation(const Simulation & s);
	Simulation(int nb, Satellite lis[]);
	~Simulation();
	
};

