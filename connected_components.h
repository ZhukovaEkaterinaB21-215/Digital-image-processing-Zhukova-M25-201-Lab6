#pragma once
#include <opencv2/core.hpp>
#include <vector>

struct Region {
    int id;
    std::vector<cv::Point> pixels;
};

std::vector<Region> label4Connected(const cv::Mat& binary);