#include <cstring>
#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <format> 
#include <sstream>
#include <fstream>

#include <opencv2/opencv.hpp>


#include "../include/convert_img.hpp"


namespace fs = std::filesystem;

namespace {

struct coutWithLineBrake { 
    template <class T>
    void operator<<(T&& out) {
        std::cout << out << '\n'; 
    }
};

} // namespace



int main(int argc, char** argv) {
    // fs::path imgPath;
    // fs::path convertImgPath;
    // size_t width;
    // try {
    //     dymmyOptionsHandler(
    //         argc, argv, imgPath, convertImgPath, width, coutWithLineBrake{}
    //     );
    // } catch (const std::exception& e) {
    //     std::cout << e.what() << '\n';
    //     return 1;
    // } 
 
    auto img = cv::imread("D:/image_to_braille/image.png", cv::ImreadModes::IMREAD_GRAYSCALE);
    int width = 200;
    double aspectRatio = static_cast<double>(img.rows) / img.cols;
    int height = static_cast<int>(width * aspectRatio); 

    cv::normalize(img, img, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::resize(img, img, cv::Size(width, height));

    std::ofstream of("D:/image_to_braille/t.txt", std::ios::binary);

    of << convert_img::toBraille(img, 80);
    
//     cv::imshow("1234", img);

//     cv::waitKey(0);
}