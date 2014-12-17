/*
 * Utils.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed, karim
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
	Mat result = imread(path, CV_LOAD_IMAGE_UNCHANGED);
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

/**
 * Select n random images
 * from a given list
 *
 * @param images	Vector of images
 * @param num		Number of images to select
 *
 *
 * @return vector of selected images
 */
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
 * Append Images
 * vertically
 *
 * @param image1		First Image
 * @param image2		Second Image
 *
 *
 * @return Appended Image
 */
Mat Utils::append_images(Mat image1, Mat image2)
{
	int max_cols;
	Mat appended;

	if (image1.cols > image2.cols)
	{
		max_cols = image1.cols;
	}
	else
	{
		max_cols = image2.cols;
	}

	appended.create(image1.rows + image2.rows, max_cols, image1.type());
	image1.copyTo(appended(Range(0, image1.rows), Range(0, image1.cols)));
	image2.copyTo(appended(Range(image1.rows, image1.rows + image2.rows), Range(0, image2.cols)));

	return appended;
}

/**
 * Append a vector of Images
 * vertically
 *
 * @param images		Vector of images
 *
 *
 * @return Appended Image
 */
Mat Utils::append_images(vector<Mat> images)
{
	Mat appended = Mat::zeros(1, 1, CV_32F);

	if (images.size() > 0)
	{
		appended = images[0];

		for (size_t i = 1; i < images.size(); i++)
		{
			appended = append_images(appended, images[i]);
		}
	}

	return appended;
}

/**
 * Split a vector into
 * two by percentage
 *
 * @param images		Vector of images
 * @param a				First vector
 * @param b				Second vector
 * @param percent		Split percent
 *
 * @return Updates vector a, b
 */
void Utils::splitByPerecent(vector<Mat> images, vector<Mat>& a, vector<Mat>& b, float percent)
{
	int max = percent * images.size();
	for (size_t i = 0; i < images.size(); i++)
	{
		if (i < max)
			a.push_back(images[i]);
		else
			b.push_back(images[i]);
	}
}

/**
 * Mask a matrix by a label
 * given a range
 *
 * @param mask			Target Mat
 * @param start			Range Start in Y
 * @param range			Range
 * @param label			Label
 *
 * @return Updates Mat mask
 */
void Utils::maskLabel(Mat& mask, int start, int range, int label)
{
	Rect area;
	area.x = 0;
	area.y = start;
	area.width = mask.cols;
	area.height = range;
	rectangle(mask, area, Scalar(label), -1);
}
