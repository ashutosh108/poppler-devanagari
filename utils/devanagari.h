#ifndef DEVANAGARI_H
#define DEVANAGARI_H

#include "HtmlOutputDev.h"

namespace devanagari {
    void convertFromTex(HtmlString &str);

    enum Char : Unicode {
        om = 0x950,
        za = 0x936,
        halant = 0x94D,
        ra = 0x930,
        _ii = 0x940,
        ma = 0x92E,
        da = 0x926,
        _a = 0x93E,
        na = 0x928,
        ta = 0x924,
    };

}
#endif
