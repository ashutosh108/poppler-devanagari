#ifndef HTMLSTRING_COMMON_HPP
#define HTMLSTRING_COMMON_HPP

#include "HtmlOutputDev.h"
#include "GfxState.h"
#include "Page.h"

// Stubs for globals from pdftohtml.cc. We can't link it because it has it's own main().
bool complexMode;
bool singleHtml;
bool ignore;
bool printCommands;
bool printHtml;
bool noframes;
bool stout;
bool xml;
bool noRoundedCoordinates;
bool showHidden;
bool noMerge;
bool devanagariConvertTex;
double wordBreakThreshold;
bool fontFullName;

class MockGfxState : GfxState {
public:
    MockGfxState(PDFRectangle *pageBox) : GfxState(
        300.0, // double hDPIA
        300.0, // double vDPIA,
        pageBox, // PDFRectangle *pageBox,
        0, // int rotateA,
        false //GBool upsideDown
    ) {
    }
    void transform(double x, double y, double * new_x, double * new_y) {
        *new_x = x;
        *new_y = y;
    }

    double getCurX() {
        return 0.0;
    }

    double getCurY() {
        return 0.0;
    }
};

// Macros are best avoided but HtmlString is non-copyable
// and non-movable so we have to improvise.
#define NEW_HTML_STRING(name, init_str) \
    PDFRectangle rect; \
    MockGfxState gfx(&rect); \
    HtmlString name((GfxState *)&gfx, 1.0, nullptr); \
    addString(name, init_str);

// unsigned to avoid converting e.g. 0x80 to 0xffffff80 on platforms with signed char
void addChar(HtmlString &s, unsigned char c) {
    s.addChar(nullptr, 10.0, 10.0, 1, 0, c);
}

void addString(HtmlString &hs, const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        addChar(hs, s[i]);
    }
}

void ensureStringIs(HtmlString & s, const char * expected) {
    int len = strlen(expected);
    BOOST_TEST(s.getLen() == len);
    int minLen = std::min(s.getLen(), len);
    for (int i = 0; i < minLen; ++i) {
        std::stringstream stream;
        stream << "s[" << i << "]: " <<
            "expected " << expected[i] << "; " <<
            "got " << s[i];
        BOOST_TEST(s[i] == expected[i], stream.str());
    }
}

#endif