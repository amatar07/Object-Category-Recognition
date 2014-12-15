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
//	string bo = "../Test-Data/images/Lenna.png";
//	x.readFolderImages("../Test-Data/TUDarmstadt/PNGImages/motorbike-testset/", "png");
	Mat f = imread("../Test-Data/images/Lenna.png", 1);
	x.createFile("../Test-Data/images/", "LANCHONN", "sift", f);
	//imshow("Original Image", source);

	waitKey(0);
	return 0;
}

