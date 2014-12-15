/*
 *  test.cpp
 *
 *  Created on: Dec 15, 2014
 *  Author: Karim Tarek, Ahmed Matar, Shawky
 */

#include "FeaturesExtraction.h"
#include "Utils.h"

int main()
{
	Mat source;
	source = imread("../Test-Data/images/Lenna.png");

	Utils x;
	string bo = "../Test-Data/images/Lenna.png";
	x.readFolderImages("../Test-Data/TUDarmstadt/PNGImages/motorbike-testset/");

//	imshow("Original Image", source);

	waitKey(0);
	return 0;
}

