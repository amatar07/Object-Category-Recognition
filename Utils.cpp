/*
 * Utils.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed
 */

#include "Utils.h"

vector<Mat> Utils::getRandomImages(vector<Mat> images, int nums)
{
	set<int> indexes;
	vector<Mat> choices;
	int max_index = images.size();
	while (indexes.size() < min(nums, max_index))
	{
		int random_index = rand() % max_index;
		if (indexes.find(random_index) == indexes.end())
		{
			choices.push_back(images[random_index]);
			indexes.insert(random_index);
		}
	}

	return choices;
}

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
	DIR *dir;
	vector<Mat> allImages;
	const char * c = path.c_str();
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
