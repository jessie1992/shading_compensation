#include <iostream>
#include <stdio.h>
#include "shading_compensation.h"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#define Debug

#ifdef Debug
#pragma comment(lib,"opencv_core340d.lib")
#pragma comment(lib,"opencv_imgcodecs340d.lib")
#pragma comment(lib,"opencv_highgui340d.lib")
#else
#pragma comment(lib,"opencv_core340.lib")
#pragma comment(lib,"opencv_imgcodecs340.lib")
#pragma comment(lib,"opencv_highgui340.lib")
#endif


cv::Mat shadingCompensation(cv::Mat input) {
	
	// Read the shading mask (16U) and convert it to 32F. 
	cv::Mat shading_mask = cv::imread("image/shading_mask_16bit.tif", cv::IMREAD_ANYDEPTH);
	shading_mask.convertTo(shading_mask, CV_32F, 0.0001, 0);

	// Convert input image (16U) to 32F.
	cv::Mat input_float, result;
	input.convertTo(input_float, CV_32F);

	// Execute input * shaing_mask and convert the result to 8U.
	result = input_float.mul(shading_mask);
	result.convertTo(result, CV_8U, 0.0625, 0);
	
	return result;
};


int main() {

	// A 12-bit image is in a 16-bit container.
	cv::Mat input = cv::imread("image/input_16bit.tif", cv::IMREAD_ANYDEPTH); // 16U

	cv::Mat result;
	result = shadingCompensation(input);

	cv::imwrite("image/result.jpg", result);

	system("pause");
	return 0;
}