#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include <algorithm>
#include "otsu.h"
#include "connected_components.h"
#include "moments.h"
#include "utils.h"

void drawFilledCircle(cv::Mat& img, int cx, int cy, int r);
void drawFilledRect(cv::Mat& img, int x1, int y1, int x2, int y2);

void runTests();