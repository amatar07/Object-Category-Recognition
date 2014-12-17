/*
 *  Classifier.h
 *
 *  Created on: Dec 16, 2014
 *  Author: Karim Tarek
 */

#ifndef CASSIFIER
#define CASSIFIER

#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "BOW.h"
#include "Utils.h"
#include <string>
#include "FeaturesExtraction.h"

using namespace std;
using namespace cv;

#define IMG_TYPE								"png"

class MyClassifier {
private:

	String srcPath, siftPath, bowPath;
	vector<Mat> sifts, bows;

	BOW bow;
	Utils util;
	Extractor extractor;

	NormalBayesClassifier naiiveClassifier;
	void calculateSIFT();
public:
	MyClassifier(String srcPath, String siftPath, String bowPath);
	void calculateBOW(Mat vocab);

	void train(Mat trainingData, Mat trainingLabels);
	void predict(Mat evalData, Mat &results);

	vector<Mat> getSifts();
	vector<Mat> getBOWs();
};

#endif

