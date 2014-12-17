/*
 *  main.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek, Ahmed Matar, Mostafa Shawky
 */

#include "Utils.h"
#include "BOW.h"
#include "Classifier.h"
#include "FeaturesExtraction.h"

int vocabDictionary = 75;
int vocabClusters = 50;
int correctLabel = 255;
float trainingDataPercent = 0.8;

// Src paths
String carpath = "../Test-Data/PNGImages/sideviews-cars/";
String motopath = "../Test-Data/PNGImages/motorbike-testset/";
String cowpath = "../Test-Data/PNGImages/sideviews-cows2/";

// Sift paths
String siftcarpath = "../Test-Data/SIFTImages/sideviews-cars/";
String siftmotopath = "../Test-Data/SIFTImages/motorbike-testset/";
String siftcowpath = "../Test-Data/SIFTImages/sideviews-cows2/";

// Bow paths
String bowcarpath = "../Test-Data/BOWImages/sideviews-cars/";
String bowmotopath = "../Test-Data/BOWImages/motorbike-testset/";
String bowcowpath = "../Test-Data/BOWImages/sideviews-cows2/";

BOW bow;
Utils util;

void generateBOWs()
{
	MyClassifier car(carpath, siftcarpath, bowcarpath);
	MyClassifier cow(cowpath, siftcowpath, bowcowpath);
	MyClassifier moto(motopath, siftmotopath, bowmotopath);

	vector<Mat> carSifts = car.getSifts();
	vector<Mat> cowSifts = cow.getSifts();
	vector<Mat> motoSifts = moto.getSifts();

	vector<Mat> randomCars = util.getRandomImages(carSifts, vocabDictionary / 3);
	vector<Mat> randomCows = util.getRandomImages(cowSifts, vocabDictionary / 3);
	vector<Mat> randomMotos = util.getRandomImages(motoSifts, vocabDictionary / 3);

	vector<Mat> vocabSet = randomCars;
	vocabSet.insert(vocabSet.end(), randomCows.begin(), randomCows.end());
	vocabSet.insert(vocabSet.end(), randomMotos.begin(), randomMotos.end());

	Mat vocab = bow.createVocab(vocabSet, vocabClusters);

	car.calculateBOW(vocab);
	cow.calculateBOW(vocab);
	moto.calculateBOW(vocab);
}

void classifiyBOWS()
{
	vector<Mat> carBOWs = util.readFolderImages(bowcarpath);
	vector<Mat> cowBOWs = util.readFolderImages(bowcowpath);
	vector<Mat> motoBOWs = util.readFolderImages(bowmotopath);

	vector<Mat> carTraining, carTesting;
	vector<Mat> cowTraining, cowTesting;
	vector<Mat> motoTraining, motoTesting;

	util.splitByPerecent(carBOWs, carTraining, carTesting, trainingDataPercent);
	util.splitByPerecent(cowBOWs, cowTraining, cowTesting, trainingDataPercent);
	util.splitByPerecent(motoBOWs, motoTraining, motoTesting, trainingDataPercent);

	vector<Mat> trainingData = carTraining;
	trainingData.insert(trainingData.end(), cowTraining.begin(), cowTraining.end());
	trainingData.insert(trainingData.end(), motoTraining.begin(), motoTraining.end());

	vector<Mat> testingData = carTesting;
	testingData.insert(testingData.end(), cowTesting.begin(), cowTesting.end());
	testingData.insert(testingData.end(), motoTesting.begin(), motoTesting.end());

	Mat trainigMat = util.append_images(trainingData);
	Mat testingMat = util.append_images(testingData);

	trainigMat.convertTo(trainigMat, CV_32FC1);
	testingMat.convertTo(testingMat, CV_32FC1);

	Mat carLabels = Mat::zeros(trainingData.size(), 1, CV_32FC1);
	Mat cowLabels = Mat::zeros(trainingData.size(), 1, CV_32FC1);
	Mat motoLabels = Mat::zeros(trainingData.size(), 1, CV_32FC1);

	util.maskLabel(carLabels, 0, carTraining.size(), correctLabel);
	util.maskLabel(cowLabels, carTraining.size(), cowTraining.size(), correctLabel);
	util.maskLabel(motoLabels, carTraining.size() + cowTraining.size(), motoTraining.size(), correctLabel);

	NormalBayesClassifier carClassifier;
	carClassifier.train(trainigMat, carLabels);

	NormalBayesClassifier cowClassifier;
	cowClassifier.train(trainigMat, cowLabels);

	NormalBayesClassifier motoClassifier;
	motoClassifier.train(trainigMat, motoLabels);

	cout << "Evaluating classifier..." << endl << endl;
	Mat carResults, cowResults, motoResults;

	carClassifier.predict(testingMat, &carResults);
	cowClassifier.predict(testingMat, &cowResults);
	motoClassifier.predict(testingMat, &motoResults);

	Mat carTestLabels = Mat::zeros(testingData.size(), 1, CV_32FC1);
	Mat cowTestLabels = Mat::zeros(testingData.size(), 1, CV_32FC1);
	Mat motoTestLabels = Mat::zeros(testingData.size(), 1, CV_32FC1);

	util.maskLabel(carTestLabels, 0, carTesting.size(), correctLabel);
	util.maskLabel(cowTestLabels, carTesting.size(), cowTesting.size(), correctLabel);
	util.maskLabel(motoTestLabels, carTesting.size() + cowTesting.size(), motoTesting.size(), correctLabel);

	float carEval, cowEval, motoEval;
	absdiff(carResults, carTestLabels, carTestLabels);
	absdiff(cowResults, cowTestLabels, cowTestLabels);
	absdiff(motoResults, motoTestLabels, motoTestLabels);

	carEval = (float) (carTestLabels.rows - countNonZero(carTestLabels)) / (float) testingMat.rows;
	cowEval = (float) (cowTestLabels.rows - countNonZero(cowTestLabels)) / (float) testingMat.rows;
	motoEval = (float) (motoTestLabels.rows - countNonZero(motoTestLabels)) / (float) testingMat.rows;

	cout << "Car-Classifier  Performance: " << carEval * 100 << "%" << endl;
	cout << "Cow-Classifier  Performance: " << cowEval * 100 << "%" << endl;
	cout << "Moto-Classifier Performance: " << motoEval * 100 << "%" << endl;

	imshow("Cars", carResults);
	imshow("Cows", cowResults);
	imshow("Moto", motoResults);
}

int main()
{
	generateBOWs();
	classifiyBOWS();

	waitKey(0);
	return 0;
}

