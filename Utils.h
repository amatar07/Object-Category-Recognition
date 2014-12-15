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
	vector<Mat> readFolderImages(string path, string imageType);
	void createFile(string path, string fileName, string fileType, Mat image);

	vector<Mat> getRandomImages(vector<Mat> images, int nums);
};

#endif
