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
#include "Utils.h"

using namespace std;
using namespace cv;

class BOW
{
private:
	Utils util;
	Mat getHistogram(Mat descriptors, Mat vocab);
public:
	vector<Mat> bagOfWords(vector<Mat> images, Mat vocab);
	Mat createVocab(vector<Mat> images, int numberCLusters);
};

#endif
