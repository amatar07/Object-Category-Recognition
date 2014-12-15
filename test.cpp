/*
 *  test.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek, Ahmed Matar, Shawky
 */

#include "Utils.h"
#include "BOW.h"

int main()
{
	Mat source1, source2, source3, output;
	source1 = imread("../Test-Data/images/Lenna.png");
	source2 = imread("../Test-Data/images/test.jpg");
	source3 = imread("../Test-Data/images/frame_18.png");

	Utils util;
	vector<Mat> images;
	images.push_back(source1);
	images.push_back(source2);
	images.push_back(source3);

	vector<Mat> choices;
	for (int j = 0; j < 3; j++)
	{
		choices = util.getRandomImages(images, 1);

		for (size_t i = 0; i < choices.size(); i++)
		{
			imshow("Original Image" + j, choices[0]);
		}
	}

	waitKey(0);
	return 0;
}

