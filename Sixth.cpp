#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <string>
#include "otsu.h"
#include "connected_components.h"
#include "moments.h"
#include "utils.h"
#include "tests.h"

int main(int argc, char** argv) {
    #ifdef _WIN32
        system("chcp 65001 >nul");
    #endif
    processImage(argv[1], "result");
    runTests();
    return 0;
}