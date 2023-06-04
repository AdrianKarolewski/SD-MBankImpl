#include <catch2/catch_test_macros.hpp>

#include "account.hpp"
#include "debitaccount.hpp"
#include "utils.hpp"

TEST_CASE("Create debAccount test", "[debAccount]") 
{
    AccountBuilder builder;
    Account account = builder
        .accountId("BM1")
        .ownerName("Adrian")
        .ownerSName("Karlewski")
        .createDate({ 3,6,2023 })
        .balance(0);

    DebitAccount debAccount(account, 1000);

    REQUIRE(debAccount.getAccountId() == "BM1");
    REQUIRE(debAccount.getOwnerName() == "Adrian");
    REQUIRE(debAccount.getOwnerSName() == "Karlewski");
    REQUIRE(account.getCreateDate() == Date::Date({ 3,6,2023 }));
    REQUIRE(debAccount.getBalance() == 0);
}
TEST_CASE("Changes with balance", "[debAccount]")
{
    AccountBuilder builder;
    Account account = builder
        .balance(0);

    DebitAccount debAccount(account, 1000);

    debAccount.changeBalance(100);
    REQUIRE(Doubles::compare(debAccount.getBalance(), 100));

    debAccount.changeBalance(300);
    REQUIRE(Doubles::compare(debAccount.getBalance(), 400));

    debAccount.changeBalance(-300);
    REQUIRE(Doubles::compare(debAccount.getBalance(), 100));
}
TEST_CASE("Change balanse to minus", "[debAccount]")
{
    AccountBuilder builder;
    Account account = builder
        .balance(0);
    
    DebitAccount debAccount(account, 1000);

    debAccount.changeBalance(-100);
    REQUIRE(Doubles::compare(debAccount.getBalance(), -100));
}
TEST_CASE("Change balanse to minus maxDebit throw exe", "[debAccount]")
{
    AccountBuilder builder;
    Account account = builder
        .balance(0);

    DebitAccount debAccount(account, 1000);

    REQUIRE_THROWS_AS(debAccount.changeBalance(-1100), MaximumDebitUsedException);
}