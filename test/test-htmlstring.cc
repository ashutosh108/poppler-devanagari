#include <cassert>
#define BOOST_TEST_MODULE HtmlString
#include <boost/test/unit_test.hpp>

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
#define NEW_HTML_STRING(name) \
    PDFRectangle rect; \
    MockGfxState gfx(&rect); \
    HtmlString name((GfxState *)&gfx, 1.0, nullptr);

void addChar(HtmlString &s, char c) {
    s.addChar(nullptr, 10.0, 10.0, 1, 0, c);
}

BOOST_AUTO_TEST_CASE(HtmlString_replaceOneCharWithEmpty) {
    NEW_HTML_STRING(s);
    addChar(s, 'a');
    addChar(s, 'b');
    addChar(s, 'c');

    s.replaceChar(1, {});

    BOOST_TEST(s.getLen() == 2);
    BOOST_TEST(s[0] == 'a');
    BOOST_TEST(s[1] == 'c');
}

BOOST_AUTO_TEST_CASE(HtmlString_replaceOneCharWithAnother) {
    NEW_HTML_STRING(s);
    addChar(s, 'a');
    addChar(s, 'b');
    addChar(s, 'c');

    s.replaceChar(1, { 'd' });

    BOOST_TEST(s.getLen() == 3);
    BOOST_TEST(s[0] == 'a');
    BOOST_TEST(s[1] == 'd');
    BOOST_TEST(s[2] == 'c');
}

BOOST_AUTO_TEST_CASE(HTMLString_replaceOneCharWithMultiple) {
    NEW_HTML_STRING(s);
    addChar(s, 'a');
    addChar(s, 'b');
    addChar(s, 'c');

    s.replaceChar(1, { 'd', 'e', 'f' });

    BOOST_TEST(s.getLen() == 5);
    BOOST_TEST(s[0] == 'a');
    BOOST_TEST(s[1] == 'd');
    BOOST_TEST(s[2] == 'e');
    BOOST_TEST(s[3] == 'f');
    BOOST_TEST(s[4] == 'c');
}