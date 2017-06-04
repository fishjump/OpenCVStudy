#include "stdafx.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void print_tips();
void run_func(int order, Mat image, Mat clone);
void salt_pepper(Mat im, double ratio);

int main()
{
	//Get image path
	cout << "input filename :" << endl;
	string file_name = "E:\\test.jpg";
	cin >> file_name;

	//Read image
	Mat image = imread(file_name);
	if (image.data == nullptr)
	{
		cout << "Failed to open this image" << endl;
		return -1;
	}

	//Select a func to run
	print_tips();
	int order = 0;
	cin >> order;
	Mat clone = image.clone();
	run_func(order, image, clone);

	//Result
	imshow("Source", image);
	imshow("Result", clone);

	waitKey();
	return 0;
}

void print_tips() {
	cout << "1.salt & pepper" << endl;
	cout << "2.median blur" << endl;
	cout << "3.blur" << endl;
	cout << "4.erode" << endl;
	cout << "5.dilate" << endl;
	cout << "Note: 2 & 3 while run 1 with ratio of 0.2" << endl;
	return;
}

void run_func(int order, Mat image, Mat clone) {
	double ratio = 0;
	int height = 0, width = 0, size = 0;
	switch (order)
	{
	case 1:
		cout << "salt & pepper ratio[0,1]:" << endl;
		cin >> ratio;
		salt_pepper(clone, ratio);
		break;
	case 2:
		salt_pepper(image, 0.2);
		cout << "Size of the kenel(an odd num):" << endl;
		cin >> size;
		medianBlur(image, clone, size);
		break;
	case 3:
		salt_pepper(image, 0.2);
		cout << "Size of the kenel(height & width , odd):" << endl;
		cin >> height >> width;
		blur(image, clone, Size(width, height));
		break;
	case 4:
		cout << "Size of the kenel(height & width , odd):" << endl;
		cin >> height >> width;
		erode(clone, clone, getStructuringElement(MORPH_RECT, Size(width, height)));
		break;
	case 5:
		cout << "Size of the kenel(height & width , odd):" << endl;
		cin >> height >> width;
		dilate(clone, clone, getStructuringElement(MORPH_RECT, Size(width, height)));
		break;
	}
}

void salt_pepper(Mat image, double ratio) {
	int pixels = image.rows*image.cols;
	int count = ratio * pixels;
	srand(time(0));

	int rows = image.rows, cols = image.cols;

	for (int i = 0;i < count;i++) {
		int y = rand() % rows,
			x = rand() % cols;

		int color = 0;
		if (rand() % 2)
			color = 255;

		Vec3b &pixel = image.at<Vec3b>(y, x);
		pixel[0] = color;
		pixel[1] = color;
		pixel[2] = color;
	}
}
