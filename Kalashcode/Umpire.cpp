#include "Umpire.h"
#include <iostream>
#include <stdio.h>
#include<time.h>	// Temps d'exec (C'est plutot du C)
#include<vector>
#include<algorithm>
#include "dirent.h"
#ifndef WIN32
	#include <sys/types.h>
#endif

Umpire::Umpire()
{
}

Umpire::~Umpire()
{
}

float Umpire::calculMoyenne(std::vector<float> vect) const
{
	float moyenne = 0;
	for (int i = 0; i < vect.size(); ++i) {
		moyenne += vect[i];
	}
	moyenne /= vect.size();
	return moyenne;
}

std::vector<std::vector<float>> Umpire::finalResult(std::vector<float> tempMoyen, std::vector<int> score)
// Cette fonction retourne un vecteur de vecteur composé de 1) l'id du programme 2) ke te
{
	std::vector<std::vector<float>> result;
	std::vector<float> temp;
	int size = tempMoyen.size();
	for (int i = 1; i <= size; i++) {
		temp.push_back(i);
		temp.push_back(tempMoyen[i-1]);
		temp.push_back(score[i-1]);
		result.push_back(temp);
		temp.clear();
	}
	return result;
}

void Umpire::sortScore(std::vector<std::vector<float>> &v)
{
	std::sort(v.begin(), v.end(), [](const std::vector<float>& a, const std::vector<float>& b) {
		return a[2] > b[2];
	});;
}

void Umpire::sortTemps(std::vector<std::vector<float>> &v)
{
	std::sort(v.begin(), v.end(), [](const std::vector<float>& a, const std::vector<float>& b) {
		return a[1] > b[1];
	});;
}

std::vector<float> Umpire::Speed(const char* path) const
{
	float time;
	int decompt = 10;
	clock_t t1, t2;
	std::vector<float> vitesseMoyenne;
	std::vector<float> listVitesseFinal;

	DIR* rep = NULL;
	struct dirent* fichierLu = NULL;
	rep = opendir(path);
	if (rep == NULL)
		exit(1);
	while ((fichierLu = readdir(rep)) != NULL)
		while (decompt != 0)
		{
			t1 = clock();
			system(fichierLu->d_name);	// Execution du programme
			t2 = clock();
			time = (float)(t2 - t1) / CLOCKS_PER_SEC;
			vitesseMoyenne.push_back(time);
			decompt--;
		}
	listVitesseFinal.push_back(calculMoyenne(vitesseMoyenne));
	if (closedir(rep) == -1)
		exit(-1);
	return listVitesseFinal;
}