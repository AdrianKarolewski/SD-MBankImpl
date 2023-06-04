#include "debitaccount.hpp"
#include "reporting.hpp"

void DebitAccount::changeBalance(const double& _amount)
{
	debitBalans += _amount;
	if (debitBalans < -maxDebit)
	{
		debitBalans += _amount;
		throw MaximumDebitUsedException("end of debit");
	}
	notify("Saldo konta o id:" + getAccountId() + "zmienio sie o" + std::to_string(_amount), _amount);
}

void DebitAccount::accept(BankProductVisitor* _visitor)
{
	_visitor->visit(this);
}