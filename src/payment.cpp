#include "payment.hpp"
#include "account.hpp"
#include "debitaccount.hpp"
#include <iostream>

void Payment::undo()
{
	Transaction::undo();
	try
	{
		// najpierw bierzemy
		toAccount.changeBalance(-amount);
		fromAccount.changeBalance(amount);
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

void Payment::execute()
{
	if (amount <= 0)
	{
		throw InvalidAmountException("invalid transfer");
	}
	Transaction::execute();
	try
	{
		// najpierw bierzemy
		fromAccount.changeBalance(-amount);
		toAccount.changeBalance(amount);
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