#include "deposit.hpp"
#include "reporting.hpp"

void Deposit::setInterrates(IInterrates* interratesCounter)
{
	interrates = interratesCounter->calculateRates();
}

void Deposit::closeDeposit()
{
	notify("Zamknieto depozyt dla konta o id " + assignedAccount.getAccountId() + "wyplacono" +
		std::to_string(depositedAmount), depositedAmount);
	if (endDate < Date::currentDate())
	{
		depositedAmount = depositedAmount * interrates;
	}
	wasClosed = true;
}

void Deposit::accept(BankProductVisitor* _visitor)
{
	_visitor->visit(this);
}