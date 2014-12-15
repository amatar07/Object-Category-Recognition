/*
 *  test.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek, Ahmed Matar, Shawky
 */

#include "FeaturesExtraction.h"

int main()
{
	Mat source;
	source = imread("../Test-Data/images/Lenna.png");
	imshow("Original Image", source);

	waitKey(0);
	return 0;
}

