/*
 *  BOW.h
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky
 */

#ifndef BOW_H
#define BOW_H

#include <math.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

using namespace std;
using namespace cv;

class BOW {
private:
	Mat getHistogram(Mat descriptors, Mat vocab);
public:
	vector<Mat> bagOfWords(vector<Mat> images, Mat vocab);
	Mat createVocab(vector<Mat> images, int numberCLusters);
	Mat append_images(Mat image1, Mat image2);
	Mat append_images(vector<Mat> images);
};

#endif
