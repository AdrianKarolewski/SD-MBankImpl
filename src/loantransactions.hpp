#pragma once

#include "loan.hpp"
#include "transaction.hpp"

class TakeLoanTransacion : public Transaction
{
public:
	TakeLoanTransacion(Loan& _loan, const std::string& _desc) :
		loan(_loan), desc(_desc) {}
	void undo() override;
	void execute() override;

	Loan& loan;
	const std::string desc;
};
class PayLoanTransaction : public Transaction
{
public:
	PayLoanTransaction(Loan& _loan, const double& _amount, const std::string& _desc) :
		loan(_loan), amount(_amount), desc(_desc) {}
	void undo() override;
	void execute() override;

	Loan& loan;
	const double amount;
	const std::string desc;
};