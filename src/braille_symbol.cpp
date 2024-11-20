#include "../include/braille_symbol.hpp"

#include <codecvt>
#include <locale>
#include <iostream>

namespace {
    // если символ <= 1 кодовой единице utf-32
    std::string get_unicode_representation(int unicode_codepoint) {
        // Преобразование Unicode-кода в строку UTF-8
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        char32_t symbol = static_cast<char32_t>(unicode_codepoint);
        return converter.to_bytes(symbol);
    }

    using namespace braille_symbol;
    void dummy_fiilB2S(std::unordered_map<BrailleSymbolDots, std::string, BrailleSymbolDotsHash>& table) {
        BrailleSymbolDots dots;
        unsigned char fillVall = 0;
        const unsigned char mask = 1;
        int unicodeCode = 0x2800;
        int x;
        for (; unicodeCode <= 0x28FF; ++unicodeCode, ++fillVall) {
            x = fillVall;
            dots.clear();
            for (size_t j = 0; j < dots.dots[0].size(); ++j) {
                for (size_t i = 0; i < dots.dots.size(); ++i) {
                    dots.dots[i][j] = static_cast<bool>(x & mask);
                    x >>= 1;
                }
            }
            auto brailleSymbol = get_unicode_representation(unicodeCode);
            table[dots] = brailleSymbol; 
        }
    }
} // namespace

namespace braille_symbol {
    BrailleSymbolDots::BrailleSymbolDots(const BrailleSymbolDots& oth) { 
        dots = oth.dots;
    }

    BrailleSymbolDots& BrailleSymbolDots::operator=(const BrailleSymbolDots& rhs) {
        dots = rhs.dots;
        return *this;
    }

    bool BrailleSymbolDots::operator==(const BrailleSymbolDots& rhs) const {
        for (std::size_t i = 0; i < rhs.dots.size(); ++i) {
            for (std::size_t j = 0; j < rhs.dots[0].size(); ++j) {
                if (dots[i][j] != rhs.dots[i][j]) { return false; }
            }
        }
        return true;
    }

    void BrailleSymbolDots::clear() noexcept {
        for (std::size_t i = 0; i < dots.size(); ++i) {
            for (std::size_t j = 0; j < dots[0].size(); ++j) {
                dots[i][j] = 0;
            }
        }
    }

    std::size_t BrailleSymbolDotsHash::operator()(const BrailleSymbolDots& s) const {
        std::size_t hash = 0;
        for (std::size_t i = 0; i < s.dots.size(); ++i) {
            for (std::size_t j = 0; j < s.dots[0].size(); ++j) {
                hash = hash * 31 + (!s.dots[i][j] ? i + j : 1);
            } 
        }
        return hash;
    }

    const std::string& dymmy_getBraille(const BrailleSymbolDots& braille) {
        static std::unordered_map<BrailleSymbolDots, std::string, BrailleSymbolDotsHash> brailleDotsToSymbol;
        if (brailleDotsToSymbol.empty()) {
            dummy_fiilB2S(brailleDotsToSymbol);
        }
        return brailleDotsToSymbol[braille];
    }


} // namespace braille_symbol
