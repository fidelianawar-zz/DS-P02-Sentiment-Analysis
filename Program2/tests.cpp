#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"

using namespace std;

TEST_CASE("DSString", "[DSString]"){
    DSString name = "fidelia";
    REQUIRE(name == "fidelia");
}
TEST_CASE("DSString +", "[DSString]"){
    DSString name = "fidelia";
    DSString name2 = " nawar";
    DSString name3 = name + name2;
    REQUIRE(name3 == "fidelia nawar");
}

TEST_CASE("DSString >", "[DSString]"){
    DSString string1 = "bac";
    DSString string2 = "abc";
    bool result = string1 < string2;
    REQUIRE(result == false);
}
TEST_CASE("DSString <", "[DSString]"){
    DSString string1 = "this is not greater";
    DSString string2 = "abc - this is greater";
    bool result = string1 < string2;
    REQUIRE(result == false);
}
TEST_CASE("DSString []", "[DSString]"){
    DSString string1 = "array of elements";
    REQUIRE(string1[0] == 'a');
}
TEST_CASE("DSString space[]", "[DSString]"){
    DSString string1 = "array of elements";
    REQUIRE(string1[5] == ' ');
}
TEST_CASE("DSString last element[]", "[DSString]"){
    DSString string1 = "array of elements";
    REQUIRE(string1[strlen(string1.c_str())-1] == 's');
}
TEST_CASE("DSString substring beginning", "[DSString]"){
    DSString string1 = "array of elements";
    REQUIRE(string1.substring(0,6) == "array ");
}
TEST_CASE("DSString last character", "[DSString]"){
    DSString string1 = "for";
    REQUIRE(string1.substring(0,2) == "fo");
}
TEST_CASE("DSString last chars", "[DSString]"){
    DSString string1 = "for";
    REQUIRE(string1.substring(0,3) == "for");
}
TEST_CASE("DSString not first index", "[DSString]"){
    DSString string1 = "for your information";
    REQUIRE(string1.substring(6,10) == "ur i");
}
TEST_CASE("DSVector quick sort", "[DSVector]"){
    DSVector<DSString> b;
    b.push_back("abcdefg");
    b.push_back("String1");
    b.push_back("hijklm");
    b.push_back("qrstuv");
    b.quickSort(0,b.getSize()-1);
    REQUIRE(b.at(0) == "String1");
}

TEST_CASE("DSVector quick sort again", "[DSVector]"){
    DSVector<DSString> b;
    b.push_back("123");
    b.push_back("string");
    b.push_back("hijklm");
    b.push_back("qrstuv");
    b.quickSort(0,b.getSize()-1);
    REQUIRE(b.at(0) == "123");
}

TEST_CASE("DSVector delete repeated", "[DSString]"){
    DSVector<DSString> b;
    b.push_back("123");
    b.push_back("123");
    b.push_back("hijklm");
    b.push_back("qrstuv");
    b.deleteRepeated();
    REQUIRE(b.getSize() == 3);
}
TEST_CASE("DSVector quick sort actual tweet", "[DSVector]"){
    DSVector<DSString> b;
    b.push_back("I");
    b.push_back("love");
    b.push_back("the");
    b.push_back("sound");
    b.push_back("of");
    b.push_back("jets");
    b.push_back("flying");
    b.push_back("overhead");
    b.push_back("It's");
    b.push_back("thrilling");
    b.push_back("and");
    b.push_back("exciting");
    b.quickSort(0,b.getSize()-1);
    REQUIRE(b.at(0) == "I");
    REQUIRE(b.at(1) == "It's");
    REQUIRE(b.at(2) == "and");
    REQUIRE(b.at(3) == "exciting");
    REQUIRE(b.at(4) == "flying");
    REQUIRE(b.binarySearch("jets") == true);
}

TEST_CASE("DSVector binary search result true", "[DSVector]"){
    DSVector<DSString> binarysearchVector;
    binarysearchVector.push_back("search");
    binarysearchVector.push_back("me");
    binarysearchVector.push_back("for");
    binarysearchVector.push_back("words");
    binarysearchVector.quickSort(0,binarysearchVector.getSize()-1);
    REQUIRE(binarysearchVector.binarySearch("search") == true);
}

TEST_CASE("DSVector binary search result false", "[DSVector]"){
    DSVector<DSString> binarysearchVector;
    binarysearchVector.push_back("search");
    binarysearchVector.push_back("me");
    binarysearchVector.push_back("for");
    binarysearchVector.push_back("words");
    binarysearchVector.quickSort(0,binarysearchVector.getSize()-1);
    REQUIRE(binarysearchVector.binarySearch("not") == false);
}

TEST_CASE("DSVector binary searching a vector, using .at()", "[DSVector]"){

    DSVector<DSString> binarysearchVector;
    DSVector<DSString> otherVector;

    binarysearchVector.push_back("search");
    binarysearchVector.push_back("me");
    binarysearchVector.push_back("for");
    binarysearchVector.push_back("words");

    otherVector.push_back("pls");
    otherVector.push_back("work");
    otherVector.push_back("search");

    binarysearchVector.quickSort(0, binarysearchVector.getSize()-1);
    otherVector.quickSort(0, otherVector.getSize()-1);

    for(int i = 0; i < otherVector.getSize(); i++){
        REQUIRE(binarysearchVector.binarySearch(otherVector.at(1)) == true);
        REQUIRE(binarysearchVector.binarySearch(otherVector.at(0)) == false);
        REQUIRE(binarysearchVector.binarySearch(otherVector.at(2)) == false);
    }
}
TEST_CASE("DSVector delete repeated words/getSize correctly", "[DSVector]"){
    DSVector<DSString> vector;
    vector.push_back("search");
    vector.push_back("me");
    vector.push_back("for");
    vector.push_back("words");
    vector.push_back("me");
    vector.quickSort(0,vector.getSize()-1);
    vector.deleteRepeated();
     REQUIRE(vector.getSize() == 4);
}

TEST_CASE("DSVector getSize()", "[DSVector]"){
    DSVector<DSString> vector;
    vector.push_back("search");
    vector.push_back("me");
    vector.push_back("for");
    vector.push_back("words");
    vector.push_back("me");
    REQUIRE(vector.getSize() == 5);
}

TEST_CASE("DSVector empty()", "[DSVector]"){
    DSVector<DSString> vector;
    REQUIRE(vector.getSize() == 0);
}

TEST_CASE("DSVector pop_back()", "[DSVector]"){
    DSVector<DSString> vector;
    vector.push_back("search");
    vector.push_back("me");
    vector.push_back("for");
    vector.pop_back();
    REQUIRE(vector.getSize() == 2);
    REQUIRE(vector.at(1) == "me");
}
