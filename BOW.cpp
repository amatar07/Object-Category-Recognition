/*
 *  BOW.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky
 */
#include "BOW.h"

/**
 * Encode each image
 * into bag of words
 *
 * @param images		Descriptors of images
 * @param vocab			Vocabulary
 *
 *
 * @return Bag of words
 */
Mat BOW::bagOfWords(vector<Mat> images, Mat vocab) {
	Mat bow(images.size(), vocab.rows, CV_16UC1);

	for (int i = 0; i < images.size(); i++) {
		Mat row = getHistogram(images[i], vocab);
		row.copyTo(bow.row(i));
	}

	return bow;
}



/**
 * Calculate histogram
 * from given image
 *
 * @param descriptors	Image descriptors
 * @param vocab			Vocabulary
 *
 *
 * @return Histogram
 */
Mat BOW::getHistogram(Mat descriptors, Mat vocab) {
	Mat histo(1, vocab.rows, CV_16UC1);

	for (int i = 0; i < descriptors.rows; i++) {
		int index = 0; double min = 0;
		for (int j = 0; j < vocab.rows; j++) {
			double temp = norm(descriptors.row(i), vocab.row(j), NORM_L2);
			if (temp < min) {
				min = temp;
				index = j;
			}
		}
		histo.at<int>(0, index) = histo.at<int>(0, index) + 1;
	}

	return histo;
}
