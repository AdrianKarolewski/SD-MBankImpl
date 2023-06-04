#include "reporting.hpp"

void BalanceReport::visit(Account* _account)
{
	raport
		.append("Konto ")
		.append(_account->getAccountId())
		.append(" bilans: ")
		.append(std::to_string(_account->getBalance()))
		.append("\n");
}

void BalanceReport::visit(DebitAccount* _debitAccount)
{
	raport
		.append("Konto debetowe ")
		.append(_debitAccount->getAccountId())
		.append(" bilans: ")
		.append(std::to_string(_debitAccount->getBalance()))
		.append("\n");
}

void BalanceReport::visit(Loan* _loan)
{
	raport
		.append("Porzyczka ")
		.append(_loan->getAssignedAccount().getAccountId())
		.append(" bilans: ")
		.append(std::to_string(_loan->getDebt()))
		.append("\n");
}

void BalanceReport::visit(Deposit* _deposit)
{
	raport
		.append("Depozyt ")
		.append(_deposit->getAssignedAccount().getAccountId())
		.append(" bilans: ")
		.append(std::to_string(_deposit->getDepositedAmount()))
		.append("\n");
}

void CreateDateReport::visit(Account* _account)
{
	Date::Date date = _account->getCreateDate();
	raport
		.append("Konto ")
		.append(_account->getAccountId())
		.append(" stworzone: ")
		.append(std::to_string(date.day)).append(".")
		.append(std::to_string(date.month)).append(".")
		.append(std::to_string(date.year)).append("r.")
		.append("\n");
}

void CreateDateReport::visit(DebitAccount* _debitAccount)
{
	Date::Date date = _debitAccount->getCreateDate();
	raport
		.append("Konto debetowe ")
		.append(_debitAccount->getAccountId())
		.append(" stworzone: ")
		.append(std::to_string(date.day)).append(".")
		.append(std::to_string(date.month)).append(".")
		.append(std::to_string(date.year)).append("r.")
		.append("\n");
}

void CreateDateReport::visit(Loan* _loan)
{
	Date::Date date = _loan->getCreateDate();
	raport
		.append("Porzyczka ")
		.append(_loan->getAssignedAccount().getAccountId())
		.append(" stworzone: ")
		.append(std::to_string(date.day)).append(".")
		.append(std::to_string(date.month)).append(".")
		.append(std::to_string(date.year)).append("r.")
		.append("\n");
}

void CreateDateReport::visit(Deposit* _deposit)
{
	Date::Date date = _deposit->getCreateDate();
	raport
		.append("Depozyt ")
		.append(_deposit->getAssignedAccount().getAccountId())
		.append(" stworzone: ")
		.append(std::to_string(date.day)).append(".")
		.append(std::to_string(date.month)).append(".")
		.append(std::to_string(date.year)).append("r.")
		.append("\n");
}