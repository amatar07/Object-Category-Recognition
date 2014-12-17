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
Mat Utils::readSingleImage(string path) {
	Mat result = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
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
vector<Mat> Utils::readFolderImages(string path, string imageType) {
	DIR *dir;
	vector<Mat> allImages;
	const char * c = path.c_str();
	struct dirent *ent;

	if ((dir = opendir(c)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string s = ent->d_name;
			if (s.find(imageType) != string::npos) {
				Mat temporary = readSingleImage(path + s);
				allImages.push_back(temporary);
			}
		}
		closedir(dir);
	} else {
		perror("");
	}

	return allImages;
}

Mat Utils::getTrainData(vector<Mat> allData) {
	Mat result = allData[0];
	BOW bow;
	int trainPercent = allData.size() * 0.8;
	for (int i = 1; i < trainPercent; i++) {
		result = bow.append_images(result, allData[i]);
	}
	return result;

}

Mat Utils::getTestData(vector<Mat> allData) {

	BOW bow;
	int trainPercent = allData.size() * 0.8;
	Mat result = allData[trainPercent];
	for (int i = trainPercent + 1; i < allData.size(); i++) {
		result = bow.append_images(result, allData[i]);
	}
	return result;
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
void Utils::createFile(string path, string fileName, string fileType,
		Mat image) {
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
vector<Mat> Utils::getRandomImages(vector<Mat> images, int nums) {
	set<int> indexes;
	vector<Mat> choices;
	int max_index = images.size();
	while (indexes.size() < min(nums, max_index)) {
		int random_index = rand() % max_index;
		if (indexes.find(random_index) == indexes.end()) {
			choices.push_back(images[random_index]);
			indexes.insert(random_index);
		}
	}

	return choices;
}
