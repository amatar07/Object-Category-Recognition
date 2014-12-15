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
#define FILEWRITETYPE 					"png"

class Utils
{
public:
	Mat readSingleImage(string path);
	vector<Mat> readFolderImages(string path, string imageType);
	void createFile(string path, string fileName, string fileType, Mat image);
};

#endif /* UTILS_H_ */
