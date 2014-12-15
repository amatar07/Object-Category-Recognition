/*
 * Utils.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Ahmed
 */

#include "Utils.h"

Mat Utils::readSingleImage(string path)
{
	Mat result = imread(path, CV_LOAD_IMAGE_COLOR);
	return result;
}

vector<Mat> Utils::readFolderImages(string path)
{
	vector<Mat> allImages;
	const char * c = path.c_str();
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(c)) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			string s = ent->d_name;

			if (s.find("png") != string::npos)
			{
				Mat temporary = readSingleImage(path + s);
				allImages.push_back(temporary);
			}
		}
		closedir(dir);
	}
	else
	{
		/* could not open directory */
		perror("");
	}
	return allImages;
}

