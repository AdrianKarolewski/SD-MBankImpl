#include "interestrates.hpp"
#include "iaccount.hpp"
#include "loan.hpp"
#include "deposit.hpp"

double AccountInterrates::calculateRates()
{
    if (account.getBalance() > 20000)
    {
        return 0.02;
    }
    return 0.03;
}

double LoanInterrates::calculateRates()
{
    double base{ 0.01 };
    if (loan.getAssignedAccount().getCreateDate() < Date::Date({ 1, 1, 2010 }))
        base -= 0.01;
    if (loan.getDebt() > 20000)
        base -= 0.01;
    return base;
}

double DepositInterrates::calculateRates()
{
    double base{ 0.01 };
    if (deposit.getAssignedAccount().getCreateDate() < Date::Date({ 1, 1, 2010 }))
        base += 0.01;
    if (deposit.getDepositedAmount() > 20000)
        base += 0.01;
    return base;
}

double PremiumDepositInterrates::calculateRates()
{
    double base{ 0.03 };
    if (deposit.getAssignedAccount().getCreateDate() < Date::Date({ 1, 1, 2010 }))
        base += 0.01;
    if (deposit.getDepositedAmount() > 20000)
        base += 0.01;
    return base;
}

double PremiumAccountInterrates::calculateRates()
{
    double base{ 0.03 };
    if (account.getCreateDate() < Date::Date({ 1, 1, 2010 }))
        base += 0.01;
    if (account.getBalance() > 20000)
        base -= 0.01;
    return base;
}

double PremiumLoanInterrates::calculateRates()
{
    double base{ 0.05 };
    if (loan.getAssignedAccount().getCreateDate() < Date::Date({ 1, 1, 2010 }))
        base -= 0.01;
    if (loan.getDebt() > 20000)
        base -= 0.01;
    return base;
}
