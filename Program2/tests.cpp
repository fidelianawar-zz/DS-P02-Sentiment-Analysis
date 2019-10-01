#include "catch.hpp"
#include "DSString.h"

TEST_CASE("DSString", "[DSString]"){
    DSString name = "fidelia";
    REQUIRE(name == "fidelia");
}
