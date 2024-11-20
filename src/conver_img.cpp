#include "../include/convert_img.hpp"
#include "../include/braille_symbol.hpp"

#include <sstream>

namespace {

using namespace braille_symbol;

int roundDownToMultiple(int value, int multiple) {
    return std::floor(value / static_cast<double>(multiple)) * multiple;
}

// CV_8U
void dummy_fillBraille(const cv::Mat& grayImg, size_t i, size_t i_lim, size_t j, size_t j_lim, BrailleSymbolDots& bsd, unsigned char threshold) {
    for (; i < i_lim; ++i) {
        for (; j < j_lim; ++j) {
            bsd.dots[i % 4][j % 2] = grayImg.at<unsigned char>(i, j) > threshold;
        }
    }
}

} // namespace 




namespace convert_img {

    //CV_8U
    std::string toBraille(const cv::Mat& grayImg, unsigned char threshold) {
        using namespace braille_symbol;
        // TODO: mb check

        std::stringstream out;
        auto height = roundDownToMultiple(grayImg.size().height, BRAILLE_HEIGHT);
        auto width = roundDownToMultiple(grayImg.size().width, BRAILLE_WIDTH);

        BrailleSymbolDots bsd;
        for (size_t i = 0; i < height - BRAILLE_HEIGHT; i += BRAILLE_HEIGHT) {
            for (size_t j = 0; j < width - BRAILLE_WIDTH; j += BRAILLE_WIDTH) {
                dummy_fillBraille(
                    grayImg, i, i+BRAILLE_HEIGHT, j, j+BRAILLE_WIDTH, bsd, threshold);
                out << dymmy_getBraille(bsd);
            }
            out << '\n';
        }
        return out.str();
    }   

} // namespace convert_img
