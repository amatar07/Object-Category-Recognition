/*
 *  BOW.h
 *
 *  Created on: Dec 15, 2014
 *  Author: Mostafa Shawky
 */

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class BOW
{
private:
	Mat getHistogram(Mat descriptors, Mat vocab);
public:
	Mat bagOfWords(vector<Mat> images, Mat vocab);
};
