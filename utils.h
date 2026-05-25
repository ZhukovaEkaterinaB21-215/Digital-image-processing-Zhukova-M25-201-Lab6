#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include "otsu.h"
#include "connected_components.h"
#include "moments.h"

cv::Mat visualizeLabels(const cv::Size& size, const std::vector<Region>& regions);
void saveResultsToCSV(const std::string& filename, const std::vector<RegionMoments>& moments, int circleCount);
void processImage(const std::string& inputPath, const std::string& outputPrefix);