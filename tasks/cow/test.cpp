#include <catch.hpp>

#include "cow_string.h"

#include <cctype>

TEST_CASE("CowString") {
    CowString str1("hello");
    REQUIRE("hello" == str1);
    CowString str2 = str1;

    REQUIRE(str1.GetData() == str2.GetData());

    str2[0] = 'h';
    REQUIRE(str1.GetData() == str2.GetData());

    str2 += " world";

    for (auto ch : str1) {
        REQUIRE(std::isalpha(ch));
    }
    CowString str3("hello_world");
    const auto* const str2_data = str2.GetData();
    const int x = 5;
    str2[x] = '_';
    REQUIRE(str3 == str2);
    REQUIRE(str2 == "hello_world");
    REQUIRE(str2_data == str2.GetData());

    str2 = str1;
    REQUIRE("hello" == str2);
    REQUIRE(str1.GetData() == str2.GetData());

    const CowString& const_str2 = str2;
    REQUIRE('e' == const_str2.At(1));

    auto it1 = str1.begin();
    auto it2 = str2.begin();
    auto const_it2 = const_str2.begin();
    *it2 = 'H';
    REQUIRE("Hello" == str2);
    REQUIRE("Hello" != str1);
    REQUIRE('h' == *it1);
    REQUIRE('H' == *it2);
    REQUIRE('H' == *const_it2);

    CowString str5("hello");
    CowString str6(" world");
    REQUIRE("hello world" == str5 + str6);
    REQUIRE("hello world" == str5 + " world");
    REQUIRE("hello world" == "hello" + str6);
}
