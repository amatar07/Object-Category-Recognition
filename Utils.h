/*
 * Utils.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed
 */

#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdio.h>
#include "sys/stat.h"
#include "stdio.h"
#include "iostream"

#include "dirent.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

#define FILEWRITETYPE 					"png"

class Utils
{
public:
	Mat readSingleImage(string path);
	Mat append_images(Mat image1, Mat image2);
	Mat append_images(vector<Mat> images);

	vector<Mat> getRandomImages(vector<Mat> images, int nums);
	vector<Mat> readFolderImages(string path, string imageType = FILEWRITETYPE);

	void createFile(string path, string fileName, string fileType, Mat image);
	void splitByPerecent(vector<Mat> images, vector<Mat>& a, vector<Mat>& b, float percent);
	void maskLabel(Mat& mask, int start, int range, int label);
};

#endif
