#pragma once

#include "deposit.hpp"
#include "transaction.hpp"

class DepositMoneyTransaction : public Transaction
{
public:
	DepositMoneyTransaction(Deposit& _deposit, const std::string& _desc) :
		deposit(_deposit), desc(_desc) {}
	void undo() override;
	void execute() override;

	Deposit& deposit;
	const std::string desc;
};
class CloseDepositTransaction : public Transaction
{
public:
	CloseDepositTransaction(Deposit& _deposit, const std::string& _desc) :
		deposit(_deposit), desc(_desc) {}
	void undo() override;
	void execute() override;

	Deposit& deposit;
	const std::string desc;
};