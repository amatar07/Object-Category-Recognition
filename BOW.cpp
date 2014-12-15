#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

Mat getVector(Mat desc, Mat vocab) {

	Mat out(1, vocab.rows, CV_16UC1);
	for (int i = 0; i < desc.rows; i++) {
		int idx = 0;
		double min = 0;
		for (int j = 0; j < vocab.rows; j++) {
			double temp = norm(desc.row(i), vocab.row(j), NORM_L2);
			if (temp < min) {
				min = temp;
				idx = j;
			}
		}
		out.at<int>(0, idx)++;
	}

	return out;
}
