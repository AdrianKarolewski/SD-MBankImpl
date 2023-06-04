#include "cardpayment.hpp"
#include "account.hpp"
#include "debitaccount.hpp"
#include <iostream>

void CardPayment::undo()
{
	Transaction::undo();
	try
	{
		// najpierw bierzemy
		toAccount.changeBalance(-amount);
		fromCard.assignedAccount.changeBalance(amount);
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

void CardPayment::execute()
{
	if (amount <= 0)
	{
		throw InvalidAmountException("invalid transfer");
	}
	Transaction::execute();
	try
	{
		// najpierw bierzemy
		fromCard.assignedAccount.changeBalance(-amount);
		toAccount.changeBalance(amount);
	}
	catch (NotEnoughtMoneyException& e)
	{
		Transaction::setInvalid();
		std::cout << e.what();
	}
	catch (MaximumDebitUsedException& e)
	{
		Transaction::execute(); // cofka do wykonanej
		std::cout << e.what();
	}
}