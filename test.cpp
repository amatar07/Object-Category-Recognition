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

	vector<Mat> images;
	images.push_back(source1);
	images.push_back(source2);
	images.push_back(source3);

	BOW bow;
	output = bow.append_images(images);

	resize(output, output, Size(output.cols / 3, output.rows / 3));
	imshow("Original Image", output);

	waitKey(0);
	return 0;
}

