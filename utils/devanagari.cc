#include "devanagari.h"

namespace devanagari {

    enum Char : Unicode {
        OM = 0x950,
        Z = 0x936,
        HALANT = 0x94D,
        R = 0x930,
        _II = 0x940,
    };

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
