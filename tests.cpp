#include "tests.h"

void drawFilledCircle(cv::Mat& img, int cx, int cy, int r) {
    int r2 = r * r;
    int x_min = std::max(0, cx - r);
    int x_max = std::min(img.cols - 1, cx + r);
    int y_min = std::max(0, cy - r);
    int y_max = std::min(img.rows - 1, cy + r);

    for (int y = y_min; y <= y_max; ++y) {
        uchar* row = img.ptr<uchar>(y);
        int dy2 = (y - cy) * (y - cy);
        for (int x = x_min; x <= x_max; ++x) {
            if ((x - cx) * (x - cx) + dy2 <= r2) {
                row[x] = 255;
            }
        }
    }
}

void drawFilledRect(cv::Mat& img, int x1, int y1, int x2, int y2) {
    int left = std::max(0, std::min(x1, x2));
    int right = std::min(img.cols - 1, std::max(x1, x2));
    int top = std::max(0, std::min(y1, y2));
    int bottom = std::min(img.rows - 1, std::max(y1, y2));

    for (int y = top; y <= bottom; ++y) {
        uchar* row = img.ptr<uchar>(y);
        for (int x = left; x <= right; ++x) {
            row[x] = 255;
        }
    }
}

void runTests() {
    {
        cv::Mat t = cv::Mat::zeros(100, 100, CV_8UC1);
        drawFilledCircle(t, 50, 50, 30);

        cv::imwrite("test1_ideal_circle.png", t);
        processImage("test1_ideal_circle.png", "res_test1");
    }

    {
        cv::Mat t = cv::Mat::zeros(150, 150, CV_8UC1);
        drawFilledCircle(t, 40, 40, 20);
        drawFilledRect(t, 80, 80, 120, 120);

        cv::imwrite("test2_circle_sq.png", t);
        processImage("test2_circle_sq.png", "res_test2");
    }

    {
        cv::Mat t = cv::Mat::zeros(50, 50, CV_8UC1);
        drawFilledRect(t, 0, 0, 9, 9);
        drawFilledRect(t, 10, 10, 19, 19);

        cv::imwrite("test3_diag_touch.png", t);
        processImage("test3_diag_touch.png", "res_test3");
    }
   
    {
        cv::Mat t = cv::Mat::zeros(100, 100, CV_8UC1);
        drawFilledCircle(t, 30, 30, 10);
        drawFilledCircle(t, 70, 70, 2);
        drawFilledCircle(t, 80, 20, 1);

        cv::imwrite("test4_area_filter.png", t);
        processImage("test4_area_filter.png", "res_test4");
    }

    {
        cv::Mat t = cv::Mat::zeros(100, 100, CV_8UC1);

        for (int y = 0; y < t.rows; ++y) {
            uchar* row = t.ptr<uchar>(y);
            for (int x = 0; x < t.cols; ++x) {
                row[x] = 100 + (rand() % 40);
            }
        }

        drawFilledCircle(t, 50, 50, 20);

        cv::imwrite("test5_noisy_bg.png", t);
        processImage("test5_noisy_bg.png", "res_test5");
    }

    {
        cv::Mat t = cv::Mat::zeros(50, 50, CV_8UC1);
        cv::imwrite("test6_empty.png", t);
        processImage("test6_empty.png", "res_test6");
    }
}