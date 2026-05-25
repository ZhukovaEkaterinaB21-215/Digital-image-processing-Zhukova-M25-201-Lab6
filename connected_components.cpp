#include "connected_components.h"
#include <queue>

std::vector<Region> label4Connected(const cv::Mat& binary) {
    if (binary.empty() || binary.channels() != 1 || binary.elemSize() != 1) {
        throw std::invalid_argument("Ожидается бинарное изображение 8 бит)");
    }
    cv::Mat labels = cv::Mat::zeros(binary.size(), CV_32S);
    std::vector<Region> regions;
    int currentLabel = 1;

    const int dirs[4][2] = { 
        {1, 0}, 
        {-1, 0}, 
        {0, 1}, 
        {0, -1} 
    };

    for (int y = 0; y < binary.rows; ++y) {
        for (int x = 0; x < binary.cols; ++x) {
            if (binary.at<uchar>(y, x) == 255 && labels.at<int>(y, x) == 0) {
                Region reg;
                reg.id = currentLabel;
                std::queue<cv::Point> q;
                q.push(cv::Point(x, y));
                labels.at<int>(y, x) = currentLabel;

                while (!q.empty()) {
                    cv::Point p = q.front(); q.pop();
                    reg.pixels.push_back(p);

                    for (const auto& d : dirs) {
                        int nx = p.x + d[0];
                        int ny = p.y + d[1];
                        if (nx >= 0 && nx < binary.cols && ny >= 0 && ny < binary.rows) {
                            if (binary.at<uchar>(ny, nx) == 255 && labels.at<int>(ny, nx) == 0) {
                                labels.at<int>(ny, nx) = currentLabel;
                                q.push(cv::Point(nx, ny));
                            }
                        }
                    }
                }
                regions.push_back(reg);
                currentLabel++;
            }
        }
    }
    return regions;
}