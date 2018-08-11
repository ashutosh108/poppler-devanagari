#define BOOST_TEST_MODULE HtmlString
#include <boost/test/unit_test.hpp>

#include "htmlstring-common.hpp"

BOOST_AUTO_TEST_CASE(HtmlString_replaceOneCharWithEmpty) {
    NEW_HTML_STRING(s, "abc");

    s.replaceChar(1, {});

    ensureStringIs(s, "ac");
}

BOOST_AUTO_TEST_CASE(HtmlString_replaceOneCharWithAnother) {
    NEW_HTML_STRING(s, "abc");

    s.replaceChar(1, { 'd' });

    ensureStringIs(s, "adc");
}

BOOST_AUTO_TEST_CASE(HTMLString_replaceOneCharWithMultiple) {
    NEW_HTML_STRING(s, "abc");

    s.replaceChar(1, { 'd', 'e', 'f' });

    ensureStringIs(s, "adefc");
}
