#include <exception>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <fstream>

#include <opencv2/opencv.hpp>


#include "../include/convert_img.hpp"
#include "../include/option_handler.hpp"


namespace fs = std::filesystem;

namespace {

struct coutWithLineBrake { 
    template <class T>
    void operator<<(T&& out) {
        std::cout << out << '\n'; 
    }
};

} // namespace


int main(int argc, char** argv) try {
    fs::path imgPath;
    fs::path convertImgPath;
    size_t width = 250;
    unsigned char threshold = 20;
    bool help = false;

    option_handler::dymmy_optionHandler(
        argc, argv, imgPath, convertImgPath, width, threshold, help, coutWithLineBrake{});

    if (help) {
        std::cout <<    
        R"( 
options:
-h - help,
-w - width,
-f - save in file,
-t - threshold
        )" << '\n';
        return 0;
    }

    auto img = cv::imread(imgPath.string(), cv::ImreadModes::IMREAD_GRAYSCALE);
    double aspectRatio = static_cast<double>(img.rows) / img.cols;
    int height = static_cast<int>(width * aspectRatio); 

    cv::normalize(img, img, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::resize(img, img, cv::Size(width, height));
    
    auto convertImg = convert_img::toBraille(img, threshold);

    if (convertImgPath.string().size()) {
        std::ofstream of(convertImgPath.string(), std::ios::binary);
        of << convertImg;
    } else {
        std::cout << convertImg;
    }
    
} catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
} catch(...) {
    std::cout << "unknown exception\n";
    return 2;
}