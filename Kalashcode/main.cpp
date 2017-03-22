#include <iostream>
#include <vector>
#include <algorithm>

#include "Satellite.h"
#include "Univers.h"
#include "ImagesCollection.h"
#include "Score.h"
#include "OutputUtil.h"
#include "Umpire.h"		// A voir si on le laisse en classe

using namespace std;

int main()
{
	// TEST fonction Umpire::result"
	//Umpire umpire;
	/*std::vector<int> score;
	score.push_back(1);
	score.push_back(2);
	score.push_back(3);
	score.push_back(56);
	score.push_back(4);
	score.push_back(5);
	score.push_back(6);
	score.push_back(7);
	score.push_back(8);
	score.push_back(9);
	std::vector<float> temps;
	for (int i = 1; i <= 10; temps.push_back(i++ * 100)) {}

	std::vector<std::vector<float>> testresult;

	testresult = umpire.finalResult(temps, score);
	std::cout << testresult[0][0] << std::endl;

	umpire.sortScore(testresult);
	std::cout << testresult[0][0] << std::endl;

	getchar();*/

	// Création d'un nouveau monde :
	Univers univers(".//res//forever_alone.in");
	//Univers univers(".//res//weekend.in");



	// TEST IA
	univers.start();


	// FIN TEST IA


	// TEST PARSING
	/*vector<Satellite> listeSatellites = univers.getListeSatellites();
	vector<ImagesCollection> listeImagesCollection = univers.getListeImagesCollection();

	std::for_each(listeSatellites.begin(), listeSatellites.end(), [](Satellite& S) {
		cout << "Satellite numero " << S.getName() << endl;
		cout << "Lattitude: " << S.getLattitude() << ", longitude: " << S.getLongitude() << ", v: " << S.getVitesse() << "\n" << endl;
	});

	getchar();


	std::for_each(listeImagesCollection.begin(), listeImagesCollection.end(), [](ImagesCollection& ic) {
		cout << "nbimg: " << ic.getNbImg()
			<< "nbtr: " << ic.getNbTimeRanges()
			<< ", score: " << ic.getScore() << endl;
	});*/
	/*
	// FIN TEST PARSING
	*/
	/*
	//test satellite
	//Fake satellite

	Satellite sat1(1,8387, 323990, 20, 5, 10);

	//cout << "combien de tour pour l'image : "<< sat1.isImageRange(8347, 175998, 10) << endl;
	cout << "latitude : " << sat1.getLattitude() << "longitude : " << sat1.getLongitude() << endl;
	cout << "next latitude : " << sat1.getNextLattitude() << "next longitude : " << sat1.getNextLongitude() << endl;
	//sat1.giveAPhoto(8347, 175998);

	sat1.setNextTurn();
	cout << sat1.getXcam() << sat1.getYcam() << endl;
	sat1.setNextTurn();
	cout << sat1.getXcam() << sat1.getYcam() << endl;
	for (size_t i = 0; i < 10; i++)
	{
		sat1.setNextTurn();

		cout << "next latitude : " << sat1.getLattitude() << "next longitude : " << sat1.getLongitude() << endl;
	}
	*//*
	Satellite s1(0, -648000, 0, -2000, 15, 4197);
	
	for (size_t i = 0; i < 10; i++)
	{
		cout << s1.getNextLattitude(i) << " " << s1.getNextLongitude(i) << endl;
	}*/
	return 0;
}