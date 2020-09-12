#ifndef IMAGE_PROCESSING_TOOLS_HPP_
#define IMAGE_PROCESSING_TOOLS_HPP_

#define MAX_BYTE 256

#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>
#include <opencv2/opencv.hpp>

int gammaPow(int srcLum, double gamma);
void setGammaArray(int gammaArray[], double gamma);
cv::Mat processFrame(int border[], int mode, const cv::Mat& oriFrame, double gamma, int gammaArray[], int edgeColorBGR[]); 

void colorEdge(cv::Mat& resultImage, int border[], int edgeColorBGR[]);
void colorRect(cv::Mat& rect, int edgeColorBGR[]);

#endif