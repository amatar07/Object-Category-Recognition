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
Mat Extractor::getDescriptors(Mat img, int xyStep) {
	Mat descriptors_mat;
	vector<KeyPoint> keypoints;
	SiftDescriptorExtractor sift_extractor;
	DenseFeatureDetector dense_detector(1.0f, 1, 0.1f, xyStep);

	img = initImg(img);
	dense_detector.detect(img, keypoints);
	sift_extractor.compute(img, keypoints, descriptors_mat);

	return descriptors_mat;
}

/**
 * Calculate the dense
 * descriptors for multiple
 * images
 *
 * @param images		The Source images
 * @param xystep		Dense xy step size
 *
 *
 * @return Vector Descriptors
 */
vector<Mat> Extractor::getDescriptors(vector<Mat> images, int xyStep) {
	vector<Mat> sifts;

	for (size_t i = 0; i < images.size(); i++) {
		sifts.push_back(getDescriptors(images[i], xyStep));
	}

	return sifts;
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
Mat Extractor::initImg(Mat img, int width, int height) {
	resize(img, img, Size(width, height));
	cvtColor(img, img, CV_BGR2GRAY);
	equalizeHist(img, img);

	return img;
}
