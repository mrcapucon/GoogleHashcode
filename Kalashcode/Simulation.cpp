#include "Simulation.h"



Simulation::Simulation()
{
}

Simulation::Simulation(int nb)
{
	nbSat = nb;
}

Simulation::Simulation(const Simulation & s)
{
	nbSat = s.nbSat;
	for (size_t i = 0; i < nbSat; i++)
	{
		listSat[i] = s.listSat;
	}
}

Simulation::Simulation(int nb, Satellite lis[])
{
	nbSat = nb;

	for (size_t i = 0; i < nb; i++)
	{
		listSat[i] = lis[i];
	}
	
}


Simulation::~Simulation()
{
}
