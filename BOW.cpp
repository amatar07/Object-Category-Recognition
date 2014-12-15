/*
 *  BOW.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky, Ahmed Matar, Karim Tarek
 */
#include "BOW.h"

/**
 * Append Images
 * vertically
 *
 * @param image1		First Image
 * @param image2		Second Image
 *
 *
 * @return Appended Image
 */
Mat BOW::append_images(Mat image1, Mat image2)
{
	int max_cols;
	Mat appended;

	if (image1.cols > image2.cols)
	{
		max_cols = image1.cols;
	}
	else
	{
		max_cols = image2.cols;
	}

	appended.create(image1.rows + image2.rows, max_cols, image1.type());
	image1.copyTo(appended(Range(0, image1.rows), Range(0, image1.cols)));
	image2.copyTo(appended(Range(image1.rows, image1.rows + image2.rows), Range(0, image2.cols)));

	return appended;
}

/**
 * Append a vector of Images
 * vertically
 *
 * @param images		Vector of images
 *
 *
 * @return Appended Image
 */
Mat BOW::append_images(vector<Mat> images)
{
	Mat appended = Mat::zeros(1, 1, CV_32F);

	if (images.size() > 0)
	{
		appended = images[0];

		for (size_t i = 1; i < images.size(); i++)
		{
			appended = append_images(appended, images[i]);
		}
	}

	return appended;
}

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
	Mat decriptors = append_images(images);

	kmeans(decriptors, clustersNum, labels, TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0), 3,
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
Mat BOW::bagOfWords(vector<Mat> images, Mat vocab)
{
	Mat bow(images.size(), vocab.rows, CV_16UC1);

	for (int i = 0; i < images.size(); i++)
	{
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
Mat BOW::getHistogram(Mat descriptors, Mat vocab)
{
	Mat histo(1, vocab.rows, CV_16UC1);

	for (int i = 0; i < descriptors.rows; i++)
	{
		int index = 0;
		double min = 0;
		for (int j = 0; j < vocab.rows; j++)
		{
			double temp = norm(descriptors.row(i), vocab.row(j), NORM_L2);
			if (temp < min)
			{
				min = temp;
				index = j;
			}
		}
		histo.at<int>(0, index) = histo.at<int>(0, index) + 1;
	}

	return histo;
}
