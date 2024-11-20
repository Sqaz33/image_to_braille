#ifndef INCLUDE_BRAILLE_SYMBOL_HPP
#define INCLUDE_BRAILLE_SYMBOL_HPP

#include <array>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <ostream>

namespace braille_symbol {
        
    static const size_t BRAILLE_WIDTH = 2;
    static const size_t BRAILLE_HEIGHT = 4;

    struct BrailleSymbolDots {
        BrailleSymbolDots() = default;
        BrailleSymbolDots(const BrailleSymbolDots& oth);
        BrailleSymbolDots& operator=(const BrailleSymbolDots& rhs);
        bool operator==(const BrailleSymbolDots& rhs) const;
        void clear() noexcept;

        std::array<std::array<bool, BRAILLE_WIDTH>, BRAILLE_HEIGHT> dots {};

        friend std::ostream& operator<<(std::ostream& out, const BrailleSymbolDots& bsd) {
            for (const auto& row : bsd.dots) {
                for (const auto& d : row) {
                    out << d;
                }
                out << '\n';
            }
            return out;
        }
    };

    struct BrailleSymbolDotsHash {
        std::size_t operator()(const BrailleSymbolDots& s) const;
    };

    const std::string& dymmy_getBraille(const BrailleSymbolDots& braille);

} // namespace_braille_symbol

#endif