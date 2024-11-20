#ifndef INCLUDE_CONVERT_IMG_HPP
#define INCLUDE_CONVERT_IMG_HPP

#include <string>

#include <opencv2/opencv.hpp>

namespace convert_img {

    // CV_8U
    std::string toBraille(const cv::Mat& grayImg, unsigned char threshold);

} // namespace convert_img

#endif