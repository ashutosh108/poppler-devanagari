#define BOOST_TEST_MODULE HtmlString
#include <boost/test/unit_test.hpp>
#include <iomanip>
#include <sstream>

#include "devanagari.h"

#include "htmlstring-common.hpp"

using namespace devanagari;

void ensureStringIs(HtmlString & s, std::initializer_list<Unicode> expected) {
    int len = expected.size();
    BOOST_TEST(s.getLen() == len);
    int minLen = std::min(s.getLen(), len);
    int i = 0;
    for (auto c : expected) {
        std::stringstream stream;
        stream << "s[" << i << "] = 0x" <<
            std::hex << std::setfill('0') << std::setw(sizeof(c) * 2) <<
            s[i] << ", expected 0x" << c;
        BOOST_TEST(s[i] == c, stream.str());
        if (++i >= minLen) break;
    }
}

BOOST_AUTO_TEST_CASE(Devanagari_OM) {
    NEW_HTML_STRING(s, ":");

    devanagari::convertFromTex(s);

    ensureStringIs(s, { devanagari::Char::OM });
}

BOOST_AUTO_TEST_CASE(Devanagari_Srii) {
    NEW_HTML_STRING(s, "\200" "F");

    devanagari::convertFromTex(s);

    ensureStringIs(s, {
        devanagari::Char::Z,
        devanagari::Char::HALANT,
        devanagari::Char::R,
        devanagari::Char::_II});
}

void devanagariTest(const char *source, std::initializer_list<Unicode> expected) {
    NEW_HTML_STRING(s, source);

    devanagari::convertFromTex(s);

    ensureStringIs(s, expected);
}

BOOST_AUTO_TEST_CASE(Devanagari_VariousLetters) {
    using namespace devanagari;
    devanagariTest("m", { Char::ma });
    devanagariTest("d", { Char::da });
}

BOOST_AUTO_TEST_CASE(Devanagari_unknownLettersAreShownAsHexCodes) {
    devanagariTest("#", { '<', '2', '3', '>' });
}
