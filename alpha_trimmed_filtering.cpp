#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#pragma comment(lib,"opencv_world490d.lib")
#else
#pragma comment(lib,"opencv_world490.lib")
#endif


Mat alphaTrimmedMean(const Mat& src, Size sz, float alpha) {		
	Mat dst;
	dst.create(src.size(), CV_32FC1);
	int y_offset = (sz.height - 1) / 2;
	int x_offset = (sz.width - 1) / 2;
	for (int y = 0; y < src.rows; y++) for (int x = 0; x<src.cols; x++) {
		vector<float> buffer;
		for (int dy = -y_offset; dy <= y_offset; dy++)for (int dx = -x_offset; dx <= x_offset; dx++) {
			int xx = x + dx;
			int yy = y + dy;
			xx = max(0, min(xx, src.cols - 1));
			yy = max(0, min(yy, src.rows - 1));
			buffer.push_back(src.at<float>(yy,xx));
			
		}
		sort(buffer.begin(), buffer.end());
		int n = buffer.size();
		int S_index = ceil(n * alpha * 0.5f);
		int E_index = floor(n * (1 - alpha * 0.5f));
		float sum = 0.0f;
		for (int i = S_index; i < E_index; i++) {
			sum += buffer[i];
		}
		float mean = sum / (E_index - S_index);
		dst.at<float>(y, x) = mean;
	}
	return dst;

}
int main(void) {
	Mat src = imread("C:/Users/choij/Desktop/noisy.png",IMREAD_GRAYSCALE); //»ÊπÈ¿∏∑Œ πﬁæ∆ø»
	Mat dst;
	dst.create(src.size(), CV_32FC1);
	Mat img32;
	
	src.convertTo(img32, CV_32F, 1 / 255.f);
	dst = alphaTrimmedMean(img32, Size(5, 5), 0.5f);
	
	imshow("Image", dst);
	waitKey();
	return 0;
}