#include "devanagari.h"

#include <map>
#include <vector>

namespace devanagari {

    void convertFromTex(HtmlString &str) {
        using Chars = std::vector<Unicode>;
        static std::map<char, Chars> map =
        {
        { ':',{ Char::om } },
        { '\200',{ Char::sha, Char::virama, Char::ra }},
        { 'F',{ Char::_ii } },
        { 'm',{ Char::ma } },
        { 'd',{ Char::da } },
        { 'd',{ Char::da } },
        { 'A',{ Char::_aa } },
        { 'n',{ Char::na } },
        { '\006',{ Char::na, Char::virama } },
        { 't',{ Char::ta } },
        { 'T',{ Char::tha } },
        { 'B',{ Char::bha } },
        { 'g',{ Char::ga } },
        { 'h',{ Char::ha } },
        { 'v',{ Char::va } },
        { '(',{ Char::ta, Char::virama} },
        { 'p',{ Char::pa } },
        { ',',{ Char::_visarga } },
        { 'r',{ Char::ra } },
        { '\213',{ Char::da, Char::virama, Char::ga } },
        { 'y',{ Char::ya } },
        { 's',{ Char::sa } },
        { '0',{ Char::zero } },
        { '1',{ Char::one} },
        { '2',{ Char::two} },
        { '3',{ Char::three } },
        { '4',{ Char::four } },
        { '5',{ Char::five } },
        { '6',{ Char::six } },
        { '7',{ Char::seven } },
        { '8',{ Char::eight } },
        { '9',{ Char::nine } },
        { 'c',{ Char::ca } },
        { '-',{ Char::sa, Char::virama } },
        { 'E',{ Char::_i } },
        { '\x09',{ Char::ssa, Char::virama } },
        { '\015',{ Char::ra, Char::virama } },
        { '\x93',{ Char::da, Char::virama, Char::ba } },
        { 'V',{ Char::tta } },
        { 'Z',{ Char::nna } },
        { '^',{ Char::virama } },
        { '\xfe',{ Char::pa, Char::virama, Char::ra } },
        { '.',{ Char::danda } },
        { ';',{ Char::double_danda } },
        { '\x89',{ Char::da, Char::virama, Char::bha } },
        { 'a',{ Char::a } },
        { 'k',{ Char::ka } },
        { 'D',{ Char::dha } },
        { 'o',{ Char::_o } },
        { '_',{ Char::_avagraha } },
        { '@',{ Char::dha, Char::virama } },
        { 'j',{ Char::ja } },
        { '\x8d',{ Char::da, Char::virama, Char::ya } },
        { '\x96',{ Char::sha, Char::virama, Char::ca } },
        { '\xe2',{ Char::ja, Char::virama, Char::nya } },
        { '\x03',{ Char::_e } },
        };

        for (int i = 0; i < str.getLen(); ++i) {
            // only process chars from 8-bit fonts
            if (str[i] >= 256) continue;
            auto found = map.find(str[i]);
            if (found != map.end()) {
                str.replaceChar(i, found->second);
                i += found->second.size() - 1;
            }
            else {
                static const char * hex = "0123456789ABCDEF";
                unsigned char hex1 = hex[(str[i] / 16) % 16];
                unsigned char hex2 = hex[str[i] % 16];
                str.replaceChar(i, { '<', hex1, hex2, '>' });
                i += 3;
            }
        }
    }

}
