/*
 *  BOW.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky, Ahmed Matar, Karim Tarek
 */
#include "BOW.h"

/**
 * Create a vocabulary
 * using a given set image
 *
 * @param images		vector of images
 * @param clustersNum	Clusters number
 *
 *
 * @return The computed vocabulary
 */
Mat BOW::createVocab(vector<Mat> images, int clustersNum)
{
	Mat labels, vocab;
	Mat decriptors = util.append_images(images);

	kmeans(decriptors, clustersNum, labels, TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 0.01), 1,
			KMEANS_PP_CENTERS, vocab);

	return vocab;
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
vector<Mat> BOW::bagOfWords(vector<Mat> images, Mat vocab)
{
	vector<Mat> bow;
	for (size_t i = 0; i < images.size(); i++)
	{
		Mat row = getHistogram(images[i], vocab);
		bow.push_back(row);
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
Mat BOW::getHistogram(Mat descriptors, Mat vocab)
{
	Mat histo = Mat::zeros(1, vocab.rows, CV_32FC1);

	for (int i = 0; i < descriptors.rows; i++)
	{
		int index = 0;
		double min = norm(descriptors.row(i), vocab.row(0), NORM_L2);
		for (int j = 0; j < vocab.rows; j++)
		{
			double temp = norm(descriptors.row(i), vocab.row(j), NORM_L2);
			if (temp < min)
			{
				min = temp;
				index = j;
			}
		}

		histo.at<float>(0, index) = float(histo.at<float>(0, index)) + 1.0;
	}

	return histo;
}
