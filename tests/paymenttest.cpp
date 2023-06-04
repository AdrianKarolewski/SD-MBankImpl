#include <catch2/catch_test_macros.hpp>

#include "iaccount.hpp"
#include "payment.hpp"
#include "utils.hpp"

namespace 
{
    class MockAccount : public IAccount
    {
    public:
        MockAccount() : balance(0) {}
        ~MockAccount() {}
        std::string getAccountId() const override { return "1"; }
        std::string getOwnerName() const override { return "A"; }
        std::string getOwnerSName() const override { return "K"; }
        Date::Date getCreateDate() const override { return { 20,11,2000 }; }
        void addToTransactionsHistory(Transaction* _t) {}
        double getBalance() const override { return balance; }
        void changeBalance(const double& _amount) override { balance += _amount; }

    private:
        double balance;
    };
}

TEST_CASE("Check payment transfer", "[payment]")
{
    MockAccount macc_from, macc_to;
    Payment p(macc_from, macc_to, 100, "");
    p.execute();

    REQUIRE(Doubles::compare(macc_from.getBalance(), -100));
    REQUIRE(Doubles::compare(macc_to.getBalance(), 100));

    p.undo();

    REQUIRE(Doubles::compare(macc_from.getBalance(), 0));
    REQUIRE(Doubles::compare(macc_to.getBalance(), 0));
}
TEST_CASE("Check payment with negativ amount", "[payment]")
{
    MockAccount macc_from, macc_to;
    Payment p(macc_from, macc_to, -100, "");
    REQUIRE_THROWS_AS(p.execute(), InvalidAmountException);
}