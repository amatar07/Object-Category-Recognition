/*
 * Utils.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed
 */

#include "Utils.h"

/**
 * reading an image
 * from given path
 *
 * @param path		image path
 *
 *
 * @return Matrix of the image
 */
Mat Utils::readSingleImage(string path)
{
	Mat result = imread(path, CV_LOAD_IMAGE_COLOR);
	return result;
}



/**
 * reading a directory
 *
 * @param path		directory path
 *
 *
 * @return vector of matricies for the images
 */
vector<Mat> Utils::readFolderImages(string path, string imageType)
{
	vector<Mat> allImages;
	const char * c = path.c_str();
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(c)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			string s = ent->d_name;
			if (s.find(imageType) != string::npos)
			{
				Mat temporary = readSingleImage(path + s);
				allImages.push_back(temporary);
			}
		}
		closedir(dir);
	}
	else
	{
		perror("");
	}

	return allImages;
}



/**
 * reading a directory
 *
 * @param path		path to add the file to
 * @param fileName	file name to save
 * @param fileType	image type to save
 * @param image		matrix image to write
 *
 *
 * @return vector of matricies for the images
 */
void Utils::createFile(string path, string fileName, string fileType, Mat image)
{
	imwrite(path + fileName + "." + fileType + "." + FILEWRITETYPE, image);
}
