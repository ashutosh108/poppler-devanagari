#include "devanagari.h"

namespace devanagari {

    void convertFromTex(HtmlString &str) {
        for (int i = 0; i < str.getLen(); ++i) {
            if (str[i] == ':') {
                str[i] = Char::OM;
            } else if (str[i] == 0x80) {
                str.replaceChar(i, { Char::Z, Char::HALANT, Char::R });
            }
        }
    }

}
