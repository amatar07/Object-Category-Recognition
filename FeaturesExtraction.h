/*
 *  FeaturesExtraction.h
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek
 */

#ifndef SIFT_EXT
#define SIFT_EXT

#include <math.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

using namespace std;
using namespace cv;

#define XY_STEP								5
#define IMG_WIDTH							300
#define IMG_HEIGHT							250

class Extractor
{
private:
	Mat initImg(Mat img, int width = IMG_WIDTH, int height = IMG_HEIGHT);
public:
	Mat getDescriptors(Mat img, int xyStep = XY_STEP);
	vector<Mat> getDescriptors(vector<Mat> images, int xyStep = XY_STEP);
};

#endif
