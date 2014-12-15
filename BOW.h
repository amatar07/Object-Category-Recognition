/*
 *  BOW.h
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky
 */

#include "opencv2/opencv.hpp"
#include "Utils.h"

using namespace std;
using namespace cv;

class BOW
{
private:
	Utils util;
	Mat getHistogram(Mat descriptors, Mat vocab);
public:
	Mat bagOfWords(vector<Mat> images, Mat vocab);
	Mat createVocab(vector<Mat> images, int numberCLusters);
	Mat append_images(Mat image1, Mat image2);
	Mat append_images(vector<Mat> images);
};
