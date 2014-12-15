/*
 *  BOW.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky, Ahmed Matar
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

Mat BOW::append_images(Mat image1, Mat image2) {
	Mat appended;
	int max_rows;
	if (image1.rows > image2.rows) {
		max_rows = image1.rows;
	} else {
		max_rows = image2.rows;
	}
	appended.create(max_rows, image1.cols + image2.cols, image1.type());
	image1.copyTo(appended(Range(0, image1.rows), Range(0, image1.cols)));
	image2.copyTo(
			appended(Range(0, image2.rows),
					Range(image1.cols, image1.cols + image2.cols)));
	return appended;
}

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

void BOW::createVocab(vector<Mat> images, int numberClusters) {

	Mat labels;
	Mat clusterPoints(images.size() * images[0].rows, images[0].cols, CV_32F);

	kmeans(clusterPoints, numberClusters, labels,
			TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0), 3,
			KMEANS_PP_CENTERS);

//	for (size_t i = 0; i < clusterPoints.size(); i++) {
//		// clusterIdx is the id of the current feautre
//		int clusterIdx = labels.at<int>(i);
//	}

}

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
		int index = 0;
		double min = 0;
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
