#include "account.hpp"
#include "transaction.hpp"
#include "reporting.hpp"

void Account::changeBalance(const double& _amount)
{
	balance += _amount;
	if (balance < 0)
	{
		balance -= _amount;
		throw NotEnoughtMoneyException("not enought money");
	}
	notify("Saldo konta o id:" + getAccountId() + "zmienio sie o" + std::to_string(_amount), _amount);
}

void Account::addToTransactionsHistory(Transaction* _t)
{
	historyOfTransactions.emplace_front(_t);
}

void Account::accept(BankProductVisitor* _visitor)
{
	_visitor->visit(this);
}