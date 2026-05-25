#include "otsu.h"
#include <vector>

int computeOtsuThreshold(const cv::Mat& gray) {
    if (gray.empty() || gray.channels() != 1 || gray.elemSize() != 1) {
        throw std::invalid_argument("Требуется полутоновое изображение 8 бит");
    }

    std::vector<int> hist(256, 0);
    int totalPixels = gray.rows * gray.cols;

    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            hist[gray.at<uchar>(y, x)]++;
        }
    }

    double sumTotal = 0.0;
    for (int i = 0; i < 256; ++i) {
        sumTotal += i * hist[i];
    }

    double sumBack = 0.0;
    double wBack = 0.0;
    double wFore = totalPixels;
    double maxVar = 0.0;
    int bestThr = 0;

    for (int t = 0; t < 256; ++t) {
        wBack += hist[t];
        if (wBack == 0) {
            continue;
        }
        wFore -= hist[t];
        if (wFore == 0) {
            break;
        }

        sumBack += t * hist[t];
        double meanBack = sumBack / wBack;
        double meanFore = (sumTotal - sumBack) / wFore;

        double var = wBack * wFore * (meanBack - meanFore) * (meanBack - meanFore);
        if (var > maxVar) {
            maxVar = var;
            bestThr = t;
        }
    }
    return bestThr;
}

cv::Mat applyThreshold(const cv::Mat& gray, int threshold) {
    cv::Mat binary = cv::Mat::zeros(gray.size(), CV_8UC1);
    for (int y = 0; y < gray.rows; ++y) {
        for (int x = 0; x < gray.cols; ++x) {
            binary.at<uchar>(y, x) = (gray.at<uchar>(y, x) > threshold) ? 255 : 0;
        }
    }
    return binary;
}