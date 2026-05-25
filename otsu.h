#pragma once
#include <opencv2/core.hpp>

int computeOtsuThreshold(const cv::Mat& gray);
cv::Mat applyThreshold(const cv::Mat& gray, int threshold);