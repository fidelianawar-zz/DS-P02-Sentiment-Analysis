#define CATCH_CONFIG_RUNNER

#include "test.h"
#include "catch.hpp"
#include <iostream>
#include <cstring>

#define TEST true
using namespace std;

int runCatchTests(int argc, char* argv[1]){
   return Catch::Session().run(argc,argv);
}

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 2 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

int main(int argc, char* argv[]){
    if(TEST){
        return runCatchTests(argc, argv);
    }
}

