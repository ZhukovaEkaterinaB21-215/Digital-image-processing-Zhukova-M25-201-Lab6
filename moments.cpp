#include "moments.h"
#include <cmath>
#include <algorithm> 

const double PI = 3.14159265358979323846;
const double CIRCLE_THRESHOLD = 0.75;

RegionMoments computeMoments(int id, const std::vector<cv::Point>& pixels) {
    RegionMoments m{};
    m.id = id;
    m.m00 = static_cast<double>(pixels.size());

    if (m.m00 == 0.0) {
        m.circularity = 0.0;
        return m;
    }

    for (const auto& p : pixels) {
        m.m10 += p.x;
        m.m01 += p.y;
    }

    m.cx = m.m10 / m.m00;
    m.cy = m.m01 / m.m00;

    for (const auto& p : pixels) {
        double dx = p.x - m.cx;
        double dy = p.y - m.cy;
        m.mu20 += dx * dx;
        m.mu02 += dy * dy;
        m.mu11 += dx * dy;
    }

    double denom = 2.0 * PI * (m.mu20 + m.mu02);
   
    if (denom > 1e-9) {
        m.circularity = (m.m00 * m.m00) / denom;
    }
    else {
        m.circularity = 0.0; 
    }

    return m;
}

int countCircleLikeRegions(const std::vector<RegionMoments>& moments, double minArea) {
    int count = 0;

    for (const auto& m : moments) {
        if (m.m00 > minArea && m.circularity > CIRCLE_THRESHOLD) {
            count++;
        }
    }
    return count;
}