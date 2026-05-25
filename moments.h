#pragma once
#include "connected_components.h"
#include <vector>

struct RegionMoments {
    int id;
    double m00, m10, m01;
    double mu20, mu02, mu11;
    double cx, cy;
    double circularity;
};


RegionMoments computeMoments(int id, const std::vector<cv::Point>& pixels);
int countCircleLikeRegions(const std::vector<RegionMoments>& moments, double minArea = 30.0);