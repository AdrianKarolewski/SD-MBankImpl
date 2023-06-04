#include "account.hpp"
#include "debitaccount.hpp"
#include <iostream>
#include "loantransactions.hpp"

void TakeLoanTransacion::undo()
{
	Transaction::undo();
	try
	{
		loan.getAssignedAccount().changeBalance(-loan.getBaseDebt());
	}
	catch (NotEnoughtMoneyException& e)
	{
		Transaction::execute(); // cofka do wykonanej
		std::cout << e.what();
	}
	catch (MaximumDebitUsedException& e)
	{
		Transaction::execute(); // cofka do wykonanej
		std::cout << e.what();
	}
}

void TakeLoanTransacion::execute()
{
	if (loan.getBaseDebt() <= 0)
	{
		throw InvalidAmountException("invalid deposit");
	}
	Transaction::execute();
	try
	{
		loan.getAssignedAccount().changeBalance(loan.getBaseDebt());
	}
	catch (NotEnoughtMoneyException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
	catch (MaximumDebitUsedException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
}

void PayLoanTransaction::undo()
{
	Transaction::undo();
	try
	{
		loan.getAssignedAccount().changeBalance(amount);
		loan.payLoan(-amount);
	}
	catch (NotEnoughtMoneyException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
	catch (MaximumDebitUsedException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
}

void PayLoanTransaction::execute()
{
	if (amount <= 0)
	{
		throw InvalidAmountException("invalid payloan amount");
	}
	Transaction::execute();
	try
	{
		loan.getAssignedAccount().changeBalance(-amount);
		loan.payLoan(amount);
	}
	catch (NotEnoughtMoneyException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
	catch (MaximumDebitUsedException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
}
