#pragma once
#include "iaccount.hpp"
#include "interestrates.hpp"
#include "balancenotifier.hpp"
#include "reportingproduct.hpp"

class Loan : public BalanceNotifier, public BankProduct
{
public:
	Loan(IAccount& _assignedAccount, const double& amount) :
		assignedAccount(_assignedAccount), baseDebt(amount), debt(amount), 
		interrates(0), createDate({ 0,0,0 }) {}
	void setInterrates(IInterrates* interratesCounter);
	IAccount& getAssignedAccount() { return assignedAccount; }
	double getDebt() { return debt; }
	double getBaseDebt() { return baseDebt; }
	Date::Date getCreateDate() { return createDate; }
	void payLoan(double _amount);

	void accept(BankProductVisitor* _visitor) override;

private:
	double baseDebt;
	double debt;
	double interrates;
	Date::Date createDate;

	IAccount& assignedAccount;
};