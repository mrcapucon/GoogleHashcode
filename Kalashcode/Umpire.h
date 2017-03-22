#pragma once
#include<string>
#include<vector>

//Classe arbitre (pas sur de la trad anglaise), objectif: juger différent executable
class Umpire
{
public:
	// Donner le path du dossier contenant tout les exec, pour qu'il les juge tous
	// Donner le path contenant chaque fichier "solution"
	Umpire();
	~Umpire();
	// Renvoie un vector des temps d'exec en float pour la précision
	std::vector<float> Speed(const char* path) const;


	// Fonction
	float calculMoyenne(std::vector<float> vect) const;
	std::vector<std::vector<float>> finalResult(std::vector<float>, std::vector<int>);
	void sortScore(std::vector<std::vector<float>>&);
	void sortTemps(std::vector<std::vector<float>>&);
};