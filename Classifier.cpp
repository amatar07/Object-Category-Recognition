/*
 *  Classifier.cpp
 *
 *  Created on: Dec 16, 2014
 *  Author: Karim Tarek
 */

#include "Classifier.h"
#include <iostream>   // std::cout
#include <string>

MyClassifier::MyClassifier(String srcPath, String siftPath, String bowPath) {
	this->srcPath = srcPath;
	this->siftPath = siftPath;
	this->bowPath = bowPath;

	calculateSIFT();
}

void MyClassifier::calculateSIFT() {
	vector<Mat> srcImages = util.readFolderImages(srcPath, IMG_TYPE);
	sifts = extractor.getDescriptors(srcImages);
	cout << srcImages.size() << " Images Loaded" << endl;

	for (size_t i = 0; i < sifts.size(); i++) {
		std::stringstream sstm;
		sstm << "image_" << i;
		string s = sstm.str();
		util.createFile(siftPath, s, "sift", sifts[i]);
	}

	cout << "SIFT Created" << endl;
}

void MyClassifier::calculateBOW(Mat vocab) {

	bows = bow.bagOfWords(sifts, vocab);

	for (size_t i = 0; i < bows.size(); i++) {
		std::stringstream sstm;
		sstm << "image_" << i;
		string s = sstm.str();
		util.createFile(bowPath, s, "bow", bows[i]);
	}

	cout << "BOW Created" << endl;
}

void MyClassifier::train(Mat trainingData, Mat trainingLabels) {
	naiiveClassifier.train(trainingData, trainingLabels);
}

void MyClassifier::predict(Mat evalData, Mat &results) {
	naiiveClassifier.predict(evalData, &results);
}

vector<Mat> MyClassifier::getSifts() {
	return sifts;
}

vector<Mat> MyClassifier::getBOWs() {
	return bows;
}
