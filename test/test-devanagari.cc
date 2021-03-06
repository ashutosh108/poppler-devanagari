#define BOOST_TEST_MODULE devanagari
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <iomanip>
#include <sstream>

#include "devanagari.h"

#include "htmlstring-common.hpp"

using namespace devanagari;

inline void ensureStringIs(HtmlString & s, std::initializer_list<Unicode> expected, char const * source) {
    int len = expected.size();
    BOOST_TEST(s.getLen() == len);
    int minLen = std::min(s.getLen(), len);
    int i = 0;
    for (auto c : expected) {
        std::stringstream stream;
        stream << "'" << source << "': s[" << i << "] = 0x" <<
            std::hex << std::setfill('0') << std::setw(sizeof(c) * 2) <<
            s[i] << ", expected 0x" << c;
        BOOST_TEST(s[i] == c, stream.str());
        if (++i >= minLen) break;
    }
}

BOOST_AUTO_TEST_CASE(Devanagari_OM) {
    NEW_HTML_STRING(s, ":");

    devanagari::convertFromTex(s);

    ensureStringIs(s, { devanagari::Char::om }, "om");
}

BOOST_AUTO_TEST_CASE(Devanagari_Srii) {
    NEW_HTML_STRING(s, "\200" "F");

    devanagari::convertFromTex(s);

    ensureStringIs(s, {
        devanagari::Char::sha,
        devanagari::Char::virama,
        devanagari::Char::ra,
        devanagari::Char::_ii}, "shrii");
}

inline void devanagariTest(const char *source, std::initializer_list<Unicode> expected) {
    NEW_HTML_STRING(s, source);

    devanagari::convertFromTex(s);

    ensureStringIs(s, expected, source);
}

BOOST_AUTO_TEST_CASE(Devanagari_VariousLetters) {
    using namespace devanagari;
    devanagariTest("m", { Char::ma });
    devanagariTest("d", { Char::da });
    devanagariTest("A", { Char::_aa });
    devanagariTest("n", { Char::na });
    devanagariTest("\006", { Char::na, Char::virama });
    devanagariTest("t", { Char::ta });
    devanagariTest("T", { Char::tha });
    devanagariTest("B", { Char::bha });
    devanagariTest("g", { Char::ga });
    devanagariTest("h", { Char::ha });
    devanagariTest("v", { Char::va });
    devanagariTest("(", { Char::ta, Char::virama });
    devanagariTest("p", { Char::pa });
    devanagariTest(",", { Char::_visarga });
    devanagariTest("r", { Char::ra });
    devanagariTest("\213", { Char::da, Char::virama, Char::ga });
    devanagariTest("y", { Char::ya });
    devanagariTest("s", { Char::sa });
    devanagariTest("0123456789", {
        Char::zero, Char::one, Char::two, Char::three, Char::four,
        Char::five, Char::six, Char::seven, Char::eight, Char::nine });
    devanagariTest("c", { Char::ca });
    devanagariTest("-t", { Char::sa, Char::virama, Char::ta });
    devanagariTest("E", { Char::_i });
    devanagariTest("\015", { Char::ra, Char::virama });
    devanagariTest("\x93", { Char::da, Char::virama, Char::ba });
    devanagariTest("V", { Char::tta });
    devanagariTest("Z", { Char::nna });
    devanagariTest("^", { Char::virama });
    devanagariTest("\xfe", { Char::pa, Char::virama, Char::ra });
    devanagariTest(".", { Char::danda });
    devanagariTest(";", { Char::double_danda });
    devanagariTest("\x89", { Char::da, Char::virama, Char::bha });
    devanagariTest("a", { Char::a });
    devanagariTest("k", { Char::ka });
    devanagariTest("D", { Char::dha });
    devanagariTest("o", { Char::_o });
    devanagariTest("_", { Char::_avagraha });
    devanagariTest("@", { Char::dha, Char::virama });
    devanagariTest("j", { Char::ja });
    devanagariTest("\x8d", { Char::da, Char::virama, Char::ya });
    devanagariTest("\x96", { Char::sha, Char::virama, Char::ca });
    devanagariTest("\xe2", { Char::ja, Char::virama, Char::nya });
    devanagariTest("\x03", { Char::_e });
    devanagariTest("\x09", { Char::ssa, Char::virama });
}

BOOST_AUTO_TEST_CASE(Devanagari_unknownLettersAreShownAsHexCodes) {
    devanagariTest("#", { '<', '2', '3', '>' });
}

BOOST_AUTO_TEST_CASE(Devanagari_keep_chars_above_255_undecoded) {
    NEW_HTML_STRING(s, "");
    addChar(s, 0x201c);

    devanagari::convertFromTex(s);

    ensureStringIs(s, { 0x201c }, "fancy quote char");
}
