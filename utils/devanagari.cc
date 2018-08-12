#include "devanagari.h"

#include <map>
#include <vector>

namespace devanagari {

    void convertFromTex(HtmlString &str) {
        using Chars = std::vector<Unicode>;
        static std::map<char, Chars> map = {
            { ':', { Char::OM } },
            { '\200', { Char::Z, Char::HALANT, Char::R }},
            { 'F', { Char::_II } },
            { 'm', { Char::ma } },
            { 'd', { Char::da } },
            { 'A', { Char::_a } },
            { 'n', { Char::na } },
            { '\006', { Char::na, Char::HALANT } },
            { 't', { Char::ta } },
        };

        for (int i = 0; i < str.getLen(); ++i) {
            auto found = map.find(str[i]);
            if (found != map.end()) {
                str.replaceChar(i, found->second);
                i += found->second.size() - 1;
            }
            else {
                static const char * hex = "0123456789ABCDEF";
                unsigned char hex1 = hex[(str[i] / 16) % 16];
                unsigned char hex2 = hex[str[i] % 16];
                str.replaceChar(i, { '<', hex1, hex2, '>' });
                i += 3;
            }
        }
    }

}
