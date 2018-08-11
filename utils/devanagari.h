#ifndef DEVANAGARI_H
#define DEVANAGARI_H

#include "HtmlOutputDev.h"

namespace devanagari {
    void convertFromTex(HtmlString &str);

    enum Char : Unicode {
        OM = 0x950,
        Z = 0x936,
        HALANT = 0x94D,
        R = 0x930,
        _II = 0x940,
        ma = 0x92E,
        da = 0x926,
    };

}
#endif
