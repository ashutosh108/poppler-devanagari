#include "devanagari.h"

#include <map>
#include <vector>

namespace devanagari {

    void convertFromTex(HtmlString &str) {
        using Chars = std::vector<Unicode>;
        static std::map<char, Chars> map =
        {
            { ':', { Char::om } },
            { '\200', { Char::sha, Char::virama, Char::ra }},
            { 'F', { Char::_ii } },
            { 'm', { Char::ma } },
            { 'd', { Char::da } },
            { 'd', { Char::da } },
            { 'A', { Char::_aa } },
            { 'n', { Char::na } },
            { '\006', { Char::na, Char::virama } },
            { 't', { Char::ta } },
            { 'T', { Char::tha } },
            { 'B', { Char::bha } },
            { 'g', { Char::ga } },
            { 'v', { Char::va } },
            { '(', { Char::ta, Char::virama} },
            { 'p', { Char::pa } },
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
