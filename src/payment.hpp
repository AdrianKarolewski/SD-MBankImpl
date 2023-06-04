#pragma once

#include "iaccount.hpp"
#include "transaction.hpp"

class Payment : public Transaction
{
public:
	Payment(IAccount& _fromAccount, IAccount& _toAccount, const double& _amount, const std::string& _desc) :
		fromAccount(_fromAccount), toAccount(_toAccount), amount(_amount), desc(_desc) {}
	void undo() override;
	void execute() override;

	IAccount& fromAccount;
	IAccount& toAccount;
	const double amount;
	const std::string desc;
};