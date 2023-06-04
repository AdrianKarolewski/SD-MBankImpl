#include <catch2/catch_test_macros.hpp>

#include "account.hpp"
#include "utils.hpp"

TEST_CASE("Create account test", "[account]") 
{
    AccountBuilder builder;
    Account account = builder
        .accountId("BM1")
        .ownerName("Adrian")
        .ownerSName("Karlewski")
        .createDate({3,6,2023})
        .balance(0);

    REQUIRE(account.getAccountId() == "BM1");
    REQUIRE(account.getOwnerName() == "Adrian");
    REQUIRE(account.getOwnerSName() == "Karlewski");
    REQUIRE(account.getCreateDate() == Date::Date({ 3,6,2023 }));
    REQUIRE(account.getBalance() == 0);
}
TEST_CASE("Changes with balance", "[account]")
{
    AccountBuilder builder;
    Account account = builder
        .balance(0);

    account.changeBalance(100);
    REQUIRE(Doubles::compare(account.getBalance(), 100));

    account.changeBalance(300);
    REQUIRE(Doubles::compare(account.getBalance(), 400));

    account.changeBalance(-300);
    REQUIRE(Doubles::compare(account.getBalance(), 100));
}
TEST_CASE("Change balanse to minus throw exc", "[accoutn]")
{
    AccountBuilder builder;
    Account account = builder
        .balance(0);
    
    REQUIRE_THROWS_AS(account.changeBalance(-100), NotEnoughtMoneyException);
}