#include "utils.h"

cv::Mat visualizeLabels(const cv::Size& size, const std::vector<Region>& regions) {
    cv::Mat vis = cv::Mat::zeros(size, CV_8UC3);
    cv::Vec3b* data = vis.ptr<cv::Vec3b>();
    int step = vis.step / sizeof(cv::Vec3b);

    for (const auto& reg : regions) {
        cv::Vec3b color(
            static_cast<uchar>((reg.id * 37) % 206 + 50),
            static_cast<uchar>((reg.id * 71) % 206 + 50),
            static_cast<uchar>((reg.id * 131) % 206 + 50)
        );
        for (const auto& p : reg.pixels) {
            data[p.y * step + p.x] = color;
        }
    }
    return vis;
}

void saveResultsToCSV(const std::string& filename, const std::vector<RegionMoments>& moments, int circleCount) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << filename << "\n";
        return;
    }

    file << std::fixed << std::setprecision(4);
    file << "ID,m00,m10,m01,cx,cy,mu20,mu02,mu11,Circularity,IsCircleLike\n";

    for (const auto& m : moments) {
        bool isCircle = (m.m00 > 30.0 && m.circularity > 0.75);
        file << m.id << ","
            << m.m00 << ","
            << m.m10 << ","
            << m.m01 << ","
            << m.cx << ","
            << m.cy << ","
            << m.mu20 << ","
            << m.mu02 << ","
            << m.mu11 << ","
            << m.circularity << ","
            << (isCircle ? "YES" : "NO") << "\n";
    }

    file << "\nTotal_CircleLike_Areas," << circleCount << "\n";
    file.close();
}


void processImage(const std::string& inputPath, const std::string& outputPrefix = "") {
    cv::Mat img = cv::imread(inputPath, cv::IMREAD_GRAYSCALE);
    if (img.empty()) { 
        std::cerr << "Ошибка загрузки: " << inputPath << "\n"; 
        return; 
    }

    int thr = computeOtsuThreshold(img);
    cv::Mat binary = applyThreshold(img, thr);
    std::cout << "Порог Оцу: " << thr << "\n";

    std::vector<Region> regions = label4Connected(binary);
    std::cout << "Найдено областей: " << regions.size() << "\n";

    std::vector<RegionMoments> moments;
    for (const auto& reg : regions) {
        moments.push_back(computeMoments(reg.id, reg.pixels));
    }

    int circleCount = countCircleLikeRegions(moments, 30.0);


    if (!outputPrefix.empty()) {
        saveResultsToCSV(outputPrefix + "_results.csv", moments, circleCount);
        cv::imwrite(outputPrefix + "_otsu.png", binary);
        cv::imwrite(outputPrefix + "_labeled.png", visualizeLabels(img.size(), regions));
    }

}