#pragma once
#include "iaccount.hpp"
#include "interestrates.hpp"
#include "balancenotifier.hpp"
#include "reportingproduct.hpp"

class Deposit : public BalanceNotifier, public BankProduct
{
public:
	Deposit(IAccount& _assignedAccount, const double& _amount) :
		assignedAccount(_assignedAccount), depositedAmount(_amount), interrates(0),
		createDate({ 0,0,0 }), endDate({ 0,0,0 }), wasClosed(false) {}
	IAccount& getAssignedAccount() { return assignedAccount; }
	double getDepositedAmount() { return depositedAmount; }
	Date::Date getCreateDate() { return createDate; }
	Date::Date getEnd() { return endDate; }
	
	void setInterrates(IInterrates* interratesCounter);
	void closeDeposit();
	bool closed() { return wasClosed; }

	void accept(BankProductVisitor* _visitor) override;

private:
	IAccount& assignedAccount;
	double depositedAmount;
	double interrates;
	Date::Date createDate;
	Date::Date endDate;
	bool wasClosed;
};