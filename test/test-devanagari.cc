#define BOOST_TEST_MODULE HtmlString
#include <boost/test/unit_test.hpp>

#include "devanagari.h"

#include "htmlstring-common.hpp"

void ensureStringIs(HtmlString & s, std::initializer_list<Unicode> expected) {
    int len = expected.size();
    BOOST_TEST(s.getLen() == len);
    int minLen = std::min(s.getLen(), len);
    int i = 0;
    for (auto c : expected) {
        BOOST_TEST(s[i] == c);
        ++i;
    }
}

BOOST_AUTO_TEST_CASE(Devanagari_OM) {
    NEW_HTML_STRING(s, ":");

    devanagari::convertFromTex(s);

    ensureStringIs(s, { devanagari::Char::OM });
}
