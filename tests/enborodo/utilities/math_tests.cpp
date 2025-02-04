#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <enborodo/utilities/math.hpp>

TEST_CASE("Wrap function tests") {
    SECTION("Basic wrapping within positive range") {
        REQUIRE(en::wrap(12.5, 0.0, 10.0) == Catch::Approx(2.5));
        REQUIRE(en::wrap(25.0, 0.0, 10.0) == Catch::Approx(5.0));
    }

    SECTION("Wrapping within negative range") {
        REQUIRE(en::wrap(-12.5, -10.0, 0.0) == Catch::Approx(-2.5));
        REQUIRE(en::wrap(-25.0, -10.0, 0.0) == Catch::Approx(-5.0));
    }

    SECTION("Wrapping within mixed negative-positive range") {
        REQUIRE(en::wrap(-5.0, -3.0, 3.0) == Catch::Approx(1.0));
        REQUIRE(en::wrap(7.0, -3.0, 3.0) == Catch::Approx(1.0));
    }

    SECTION("Value already in range remains unchanged") {
        REQUIRE(en::wrap(2.5, 0.0, 10.0) == Catch::Approx(2.5));
        REQUIRE(en::wrap(-2.5, -10.0, 0.0) == Catch::Approx(-2.5));
    }

    SECTION("Exception thrown if max <= min") {
        REQUIRE_THROWS_AS(en::wrap(5.0, 10.0, 10.0), std::invalid_argument);
        REQUIRE_THROWS_AS(en::wrap(5.0, 10.0, 5.0), std::invalid_argument);
    }
}
