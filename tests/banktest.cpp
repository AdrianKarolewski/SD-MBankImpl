#include <catch2/catch_test_macros.hpp>

#include "bank.hpp"

TEST_CASE("Check bank create account", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto account = bank->createAccount("adrian", "karolewski");
    REQUIRE(bank->getAccount(account->getAccountId()));
}
TEST_CASE("Chect bank account indexing", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto account1 = bank->createAccount("adrian", "karolewski");
    REQUIRE(account1->getAccountId() == "newBankA1");

    auto account2 = bank->createAccount("adrian", "karolewski");
    REQUIRE(account2->getAccountId() == "newBankA2");
}
TEST_CASE("Chect bank create account with currdate", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto account1 = bank->createAccount("adrian", "karolewski");
    REQUIRE(account1->getCreateDate() == Date::currentDate());
}
TEST_CASE("Check bank create debtaccount", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto daccount = bank->createDebitAccount("adrian", "karolewski",1000);
    REQUIRE(bank->getAccount(daccount->getAccountId()));
}
TEST_CASE("Chect bank account debtaccount", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto daccount1 = bank->createDebitAccount("adrian", "karolewski", 1000);
    REQUIRE(daccount1->getAccountId() == "newBankD1");

    auto daccount2 = bank->createDebitAccount("adrian", "karolewski", 1000);
    REQUIRE(daccount2->getAccountId() == "newBankD2");
}
TEST_CASE("Chect bank create debtaccount with currdate", "[bank]")
{
    auto bank = Bank::createBank("newBank");
    auto daccount1 = bank->createDebitAccount("adrian", "karolewski", 1000);
    REQUIRE(daccount1->getCreateDate() == Date::currentDate());
}