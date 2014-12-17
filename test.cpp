/*
 *  test.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek, Ahmed Matar, Mostafa Shawky
 */

#include "Utils.h"
#include "BOW.h"
#include "Classifier.h"
#include "FeaturesExtraction.h"

Mat mergeTrainData(vector<Mat> carsBOWs, vector<Mat> cowsBOWs,
		vector<Mat> motoBOWs, BOW bow, Utils util) {
	Mat carBowsMatrix = util.getTrainData(carsBOWs);
	Mat cowsBowsMatrix = util.getTrainData(cowsBOWs);
	Mat motoBowsMatrix = util.getTrainData(motoBOWs);
	Mat allTrainBows = bow.append_images(carBowsMatrix, cowsBowsMatrix);

	allTrainBows = bow.append_images(allTrainBows, motoBowsMatrix);
	return allTrainBows;
}

Mat mergeTestData(vector<Mat> carsBOWs, vector<Mat> cowsBOWs,
		vector<Mat> motoBOWs, BOW bow, Utils util) {
	Mat carBowsMatrix = util.getTestData(carsBOWs);
	Mat cowsBowsMatrix = util.getTestData(cowsBOWs);
	Mat motoBowsMatrix = util.getTestData(motoBOWs);
	Mat allTestBows = bow.append_images(carBowsMatrix, cowsBowsMatrix);
	allTestBows = bow.append_images(allTestBows, motoBowsMatrix);
	return allTestBows;
}

Mat maskingLabel(vector<Mat> carsBOWs, vector<Mat> cowsBOWs,
		vector<Mat> motoBOWs, BOW bow, Utils util, int typeCode) {
	Mat carBowsMatrix = util.getTestData(carsBOWs);
	Mat cowsBowsMatrix = util.getTestData(cowsBOWs);
	Mat motoBowsMatrix = util.getTestData(motoBOWs);
	carBowsMatrix = Scalar(0);
	cowsBowsMatrix = Scalar(0);
	motoBowsMatrix = Scalar(0);

	if (typeCode == 1) {
		carBowsMatrix = Scalar(1);
	} else if (typeCode == 2) {
		cowsBowsMatrix = Scalar(1);
	} else if (typeCode == 3) {
		motoBowsMatrix = Scalar(1);
	}
	Mat allTestBows = bow.append_images(carBowsMatrix, cowsBowsMatrix);
	allTestBows = bow.append_images(allTestBows, motoBowsMatrix);
	return allTestBows;
}

int main() {

	Utils util;
	BOW bow;

	//src paths
	String motopath = "../Test-Data/PNGImages/motorbike-testset/";
	String carpath = "../Test-Data/PNGImages/sideviews-cars/";
	String cowpath = "../Test-Data/PNGImages/sideviews-cows2/";

	//sift paths
	String siftmotopath = "../Test-Data/SIFTImages/motorbike-testset/";
	String siftcarpath = "../Test-Data/SIFTImages/sideviews-cars/";
	String siftcowpath = "../Test-Data/SIFTImages/sideviews-cows2/";

	//bow paths
	String bowmotopath = "../Test-Data/BOWImages/motorbike-testset/";
	String bowcarpath = "../Test-Data/BOWImages/sideviews-cars/";
	String bowcowpath = "../Test-Data/BOWImages/sideviews-cows2/";

	//MyClassifier car(carpath, siftcarpath, bowcarpath);
	//MyClassifier cow(cowpath, siftcowpath, bowcowpath);
	//MyClassifier moto(motopath, siftmotopath, bowmotopath);

	//vector<Mat> carSifts = car.getSifts();
	//vector<Mat> cowSifts = cow.getSifts();
	//vector<Mat> motoSifts = moto.getSifts();

	//vector<Mat> randomCars = util.getRandomImages(carSifts, 25);
	//vector<Mat> randomCows = util.getRandomImages(cowSifts, 25);
	//vector<Mat> randomMotos = util.getRandomImages(motoSifts, 25);

	//vector<Mat> vocabSet = randomCars;

	//vocabSet.insert(vocabSet.end(), randomCows.begin(), randomCows.end());
	//vocabSet.insert(vocabSet.end(), randomMotos.begin(), randomMotos.end());

	//cout << "Vocab Size:" << vocabSet.size() << endl;
	//Mat vocab = bow.createVocab(vocabSet, 100);

	//car.calculateBOW(vocab);
	//cow.calculateBOW(vocab);
	//moto.calculateBOW(vocab);

//////////////            ////////////////////

	vector<Mat> carsBOWs = util.readFolderImages(bowcarpath);
	vector<Mat> cowsBOWs = util.readFolderImages(bowcowpath);
	vector<Mat> motoBOWs = util.readFolderImages(bowmotopath);

	Mat allTrainData = mergeTrainData(carsBOWs, cowsBOWs, motoBOWs, bow, util);
	Mat allTestData = mergeTestData(carsBOWs, cowsBOWs, motoBOWs, bow, util);

	Mat carLabel = maskingLabel(carsBOWs, cowsBOWs, motoBOWs, bow, util, 1);
	Mat cowLabel = maskingLabel(carsBOWs, cowsBOWs, motoBOWs, bow, util, 2);
	Mat motoLabel = maskingLabel(carsBOWs, cowsBOWs, motoBOWs, bow, util, 3);



	////////////////////////////////////
	Mat m1 = Mat(1, 1, CV_32F);
	//or even
	Mat m2 = Mat(1, 1, CV_32F);

	NormalBayesClassifier naiiveClassifier;
	naiiveClassifier.train(allTrainData, carLabel);
	//naiiveClassifier.train(m1, m2);
//////////////////////////////////////////
	waitKey(0);
	return 0;
}

