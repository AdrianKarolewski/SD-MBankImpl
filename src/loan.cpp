#include "loan.hpp"
#include "reporting.hpp"

void Loan::setInterrates(IInterrates* interratesCounter)
{
	interrates = interratesCounter->calculateRates();
	debt = baseDebt + (baseDebt * interrates);
}

void Loan::payLoan(double _amount)
{
	notify("Dlug do konta o id:" + assignedAccount.getAccountId() + "zostal splacony o" 
		+ std::to_string(_amount), _amount);
	if (_amount > 0)
	{
		debt -= _amount;
		baseDebt -= _amount;
	}
}

void Loan::accept(BankProductVisitor* _visitor)
{
	_visitor->visit(this);
}