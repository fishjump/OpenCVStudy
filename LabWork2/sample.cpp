#include <iostream>
#include <vector>
#include <opencv2\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

bool cmp(Rect a, Rect b);
Rect combin(Rect a, Rect b);
bool condition(Rect a, Rect b, Mat im);

bool rect_combine(Mat im, vector<Rect> &vec_rects,
	vector<Rect>&vec_rects_out, bool(*condition)(Rect a, Rect b, Mat im));

int main() {

	Mat im = imread("E://timg.jpg");
	Mat gray;
	cvtColor(im, gray, CV_BGR2GRAY);
	blur(gray, gray, Size(3, 3));

	Sobel(gray, gray, gray.depth(), 2, 0, 3);

	threshold(gray, gray, 0, 255, CV_THRESH_OTSU);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(1, 3));
	dilate(gray, gray, kernel, Point(-1, -1), 4);
	erode(gray, gray, kernel, Point(-1, -1), 8);
	dilate(gray, gray, kernel, Point(-1, -1), 4);

	kernel = getStructuringElement(MORPH_RECT, Size(3, 1));
	erode(gray, gray, kernel, Point(-1, -1), 1);
	dilate(gray, gray, kernel, Point(-1, -1), 8);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(gray, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);


	Mat copy = im.clone();
	vector<Rect> rects;
	for (int i = 0;i < contours.size();i++) {
		rects.push_back(boundingRect(contours[i]));
	}
	sort(rects.begin(), rects.end(), cmp);

	vector<Rect> res;
	rect_combine(copy, rects, res, condition);

	for (int i = 0;i<res.size();i++) {
		rectangle(copy, res[i], Scalar(0, 0, 255), 3);
	}

	return 0;
}

bool cmp(Rect a, Rect b) {
	return a.y < b.y;
}

Rect combin(Rect a, Rect b) {
	Point atl = a.tl(), btl = b.tl();
	Point abr = a.br(), bbr = b.br();
	Rect temp(Point(atl.x < btl.x ? atl.x : btl.x, atl.y < btl.y ? atl.y : btl.y),
		Point(abr.x > bbr.x ? abr.x : bbr.x, abr.y > bbr.y ? abr.y : bbr.y));

	return temp;
}

bool condition(Rect a, Rect b, Mat im) {
	bool is_good = true;
	Point atl = a.tl(), btl = b.tl();
	if (!((btl.x - atl.x - a.width) < (im.size().width / 10)))
		is_good = false;

	if (!((btl.y - atl.y - a.height) < im.size().height / 10))
		is_good = false;

	Rect r = combin(a, b);
	double whratio = r.width / (double)r.height;
	if (!(3.0 <= whratio && whratio <= 7.0))
		is_good = false;

	if (!(r.width > (im.size().width / 10)))
		is_good = false;

	if (!(im.size().width / 10 < r.tl().x&&r.tl().x < im.size().width / 10 * 9))
		is_good = false;

	cout << is_good << endl;
	return is_good;
}

bool rect_combine(Mat im, vector<Rect> &vec_rects,
	vector<Rect>&vec_rects_out, bool(*condition)(Rect a, Rect b, Mat im)) {
	int size = vec_rects.size();
	for (int i = 0;i < size - 1;i++) {
		cout << i << endl;
		if (condition(vec_rects[i], vec_rects[i + 1], im)) {
			vec_rects_out.push_back(combin(vec_rects[i], vec_rects[i + 1]));
		}
	}
	return true;
}