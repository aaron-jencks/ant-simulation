#include <random>

#include "doctest.h"
#include <engine/vector.hpp>

std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> rand_float(0, 1000);

TEST_CASE("Vector Magnitude") {
    engine::Vector2<float> v{3.0f, 4.0f};
    CHECK(v.magnitude() == doctest::Approx(5.0f));
}

TEST_CASE("Normalize a Zero Unit Vector") {
    auto v = engine::Vector2<float>{0.0f, 0.0f}.unit();

    CHECK(v.x == 0.0);
    CHECK(v.y == 0.0);
}

TEST_CASE("Vector Addition") {
    float ax = rand_float(rng), ay = rand_float(rng), bx = rand_float(rng), by = rand_float(rng);
    float xo = ax + bx, yo = ay + by;
    engine::Vector2<float> a{ax, ay}, b{bx, by}, c;

    SUBCASE("Non-Inplace") {
        c = a + b;
        CHECK(a.x == ax);
        CHECK(a.y == ay);
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(c.x == xo);
        REQUIRE(c.y == yo);
    }

    SUBCASE("Inplace") {
        a += b;
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(a.x == xo);
        REQUIRE(a.y == yo);
    }
}

TEST_CASE("Vector Subtraction") {
    float ax = rand_float(rng), ay = rand_float(rng), bx = rand_float(rng), by = rand_float(rng);
    float xo = ax - bx, yo = ay - by;
    engine::Vector2<float> a{ax, ay}, b{bx, by}, c;

    SUBCASE("Non-Inplace") {
        c = a - b;
        CHECK(a.x == ax);
        CHECK(a.y == ay);
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(c.x == xo);
        REQUIRE(c.y == yo);
    }

    SUBCASE("Inplace") {
        a -= b;
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(a.x == xo);
        REQUIRE(a.y == yo);
    }
}

TEST_CASE("Vector Multiplication") {
    float ax = rand_float(rng), ay = rand_float(rng), bx = rand_float(rng), by = rand_float(rng);
    float xo = ax * bx, yo = ay * by;
    engine::Vector2<float> a{ax, ay}, b{bx, by}, c;

    SUBCASE("Non-Inplace") {
        c = a * b;
        CHECK(a.x == ax);
        CHECK(a.y == ay);
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(c.x == xo);
        REQUIRE(c.y == yo);
    }

    SUBCASE("Inplace") {
        a *= b;
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(a.x == xo);
        REQUIRE(a.y == yo);
    }
}

TEST_CASE("Vector Division") {
    float ax = rand_float(rng), ay = rand_float(rng), bx = rand_float(rng) + 1, by = rand_float(rng) + 1;
    float xo = ax / bx, yo = ay / by;
    engine::Vector2<float> a{ax, ay}, b{bx, by}, c;

    SUBCASE("Non-Inplace") {
        c = a / b;
        CHECK(a.x == ax);
        CHECK(a.y == ay);
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(c.x == xo);
        REQUIRE(c.y == yo);
    }

    SUBCASE("Inplace") {
        a /= b;
        CHECK(b.x == bx);
        CHECK(b.y == by);
        REQUIRE(a.x == xo);
        REQUIRE(a.y == yo);
    }
}
