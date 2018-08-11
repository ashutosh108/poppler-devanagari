#include "devanagari.h"

namespace devanagari {

    void convertFromTex(HtmlString &str) {
        for (int i = 0; i < str.getLen(); ++i) {
            if (str[i] == ':') {
                str[i] = Char::OM;
            }
            else if (str[i] == 0x80) {
                str.replaceChar(i, { Char::Z, Char::HALANT, Char::R });
                i += 2;
            }
            else if (str[i] == 'F') {
                str.replaceChar(i, { Char::_II });
            }
            else if (str[i] == 'm') {
                str.replaceChar(i, { Char::ma });
            }
            else if (str[i] == 'd') {
                str.replaceChar(i, { Char::da });
            }
            else if (str[i] == 'A') {
                str.replaceChar(i, { Char::_a });
            }
            else if (str[i] == 'n') {
                str.replaceChar(i, { Char::na });
            }
            else if (str[i] == '\006') {
                str.replaceChar(i, { Char::na, Char::HALANT });
                i += 1;
            }
            else if (str[i] == 't') {
                str.replaceChar(i, { Char::ta });
            }
            else {
                static const char * hex = "0123456789ABCDEF";
                unsigned char hex1 = hex[(str[i] / 16) % 16];
                unsigned char hex2 = hex[ str[i] % 16];
                str.replaceChar(i, { '<', hex1, hex2, '>' });
                i += 3;
            }
        }
    }

}
