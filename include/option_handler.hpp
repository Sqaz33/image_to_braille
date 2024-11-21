#ifndef INCLUDE_OPTION_HANDLER_HPP
#define INCLUDE_OPTION_HANDLER_HPP

#include <filesystem>

namespace option_handler {
    const size_t WIN_MAX_PATH = 260;

    template <class WOut>
    void dymmy_optionHandler(
        int argc, 
        char* const* argv,
        std::filesystem::path& imgPath,
        std::filesystem::path& convertImgPath,
        size_t& width,
        unsigned char& threshold,
        bool& help,
        WOut&& warningsOut) 
    {   
        if (argc == 1) {
            throw std::logic_error("The path to the image is not specified.");
        }

        char* buf = new char[WIN_MAX_PATH];
        for (int i = 1; i < argc; ++i) {
            strcpy_s(buf, WIN_MAX_PATH, argv[i]);
            if (std::strstr(buf, "-f") && i < argc - 1) {
                strcpy_s(buf, WIN_MAX_PATH, argv[++i]);
                std::stringstream ss;
                ss << buf;
                ss >> convertImgPath;
            } else if (std::strstr(buf, "-w") && i < argc - 1) {
                strcpy_s(buf, WIN_MAX_PATH, argv[++i]);
                std::stringstream ss;
                ss << buf;
                ss >> width;
            } else if (std::strstr(buf, "-t") && i < argc - 1) {
                strcpy_s(buf, WIN_MAX_PATH, argv[++i]);
                std::stringstream ss;
                ss << buf;
                ss >> threshold;
            } else if (std::strstr(buf, "-h")) {
                help = true;
                return;
            } else if (buf[0] == '-') {
                warningsOut << std::format("Unknown option: {}", buf);
            } else {
                std::stringstream ss;
                ss << buf;
                ss >> imgPath;
            }

        }
        
    }

} // namespace option_handler


#endif // INCLUDE_OPTION_HANDLER_HPP