/*
 *  FeaturesExtraction.h
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek
 */
#include "FeaturesExtraction.h"

/**
 * Calculate the dense
 * descriptors
 *
 * @param img			The Source image
 * @param xystep		Dense xy step size
 *
 *
 * @return Descriptors
 */
Mat Extractor::getDescriptors(Mat img, int xyStep)
{
	Mat descriptors_mat;
	vector<KeyPoint> keypoints;
	SiftDescriptorExtractor sift_extractor;
	DenseFeatureDetector dense_detector(1.0f, 1, 0.1f, xyStep);

	dense_detector.detect(img, keypoints);
	sift_extractor.compute(img, keypoints, descriptors_mat);

	return descriptors_mat;
}



/**
 * Initialize an image
 * by resizing, grayscale
 *
 * @param img			The Source image
 * @param width			Target width
 * @param height		Target height
 *
 *
 * @return Resized equalized Image
 */
Mat Extractor::initImg(Mat img, int width, int height)
{
	resize(img, img, Size(width, height));
	cvtColor(img, img, CV_BGR2GRAY);
	equalizeHist(img, img);

	return img;
}
