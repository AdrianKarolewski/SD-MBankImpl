#include <catch2/catch_test_macros.hpp>

#include "transaction.hpp"

TEST_CASE("Check transaction state", "[transaction]")
{
    Transaction t;
    t.execute();
    REQUIRE(t.wasExecuted());
    REQUIRE_THROWS_AS(t.execute(), TansactionStateException);

    t.undo();
    REQUIRE(!t.wasExecuted());
    REQUIRE_THROWS_AS(t.undo(), TansactionStateException);

    t.setInvalid();
    REQUIRE(t.isInvalid());
    REQUIRE_THROWS_AS(t.execute(), InvalidTansactionException);
}