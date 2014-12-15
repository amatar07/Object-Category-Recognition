/*
 * Utils.h
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed
 */

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

#ifndef UTILS_H_
#define UTILS_H_

class Utils
{
public:
	vector<Mat> readFolderImages(string path);
	Mat readSingleImage(string path);
};

#endif /* UTILS_H_ */
