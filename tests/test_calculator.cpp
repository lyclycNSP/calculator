#define CATCH_CONFIG_MAIN  // 让 Catch2 生成 main() 函数
#include "catch.hpp"

#include "../lib/calculator.h"
#include "../lib/addition.h"
#include "../lib/subtraction.h"
#include "../lib/multiplication.h"
#include "../lib/division.h"

char method = 'r';
long long prec = -1;

TEST_CASE("Addition", "[addition]") {
    string fir = "0";
    string symbol = "+";
    REQUIRE(calculator::calculation(fir, symbol, "0", method, prec) == "0");
    REQUIRE(calculator::calculation(fir, symbol, "1.1", method, prec) == "1.1");
}
