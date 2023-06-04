#include "account.hpp"
#include "debitaccount.hpp"
#include <iostream>
#include "deposittransactions.hpp"

void CloseDepositTransaction::undo()
{
	Transaction::undo();
	try
	{
		deposit.getAssignedAccount().changeBalance(deposit.getDepositedAmount());
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

void CloseDepositTransaction::execute()
{
	if (deposit.closed())
	{
		Transaction::setInvalid();
		return;
	}
	Transaction::execute();
	try
	{
		deposit.closeDeposit();
		deposit.getAssignedAccount().changeBalance(deposit.getDepositedAmount());
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

void DepositMoneyTransaction::undo()
{
	Transaction::undo();
	try
	{
		deposit.getAssignedAccount().changeBalance(deposit.getDepositedAmount());
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

void DepositMoneyTransaction::execute()
{
	if (deposit.getDepositedAmount() <= 0)
	{
		throw InvalidAmountException("invalid deposit");
		Transaction::setInvalid();
		return;
	}
	Transaction::execute();
	try
	{
		deposit.getAssignedAccount().changeBalance(-deposit.getDepositedAmount());
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