#pragma once

#include "iaccount.hpp"
#include "transaction.hpp"

struct Card
{
	const unsigned int nr;
	int pin;
	IAccount& assignedAccount;
};

class CardPayment : public Transaction
{
public:
	CardPayment(Card& _fromCard, IAccount& _toAccount, const double& _amount, const std::string& _desc) :
		fromCard(_fromCard), toAccount(_toAccount), amount(_amount), desc(_desc) {}
	void undo() override;
	void execute() override;

	Card& fromCard;
	IAccount& toAccount;
	const double amount;
	const std::string desc;
};