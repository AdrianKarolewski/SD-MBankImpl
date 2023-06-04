#pragma once

#include "iaccount.hpp"
#include "balancenotifier.hpp"
#include "reportingproduct.hpp"

class BankProductVisitor;

class DebitAccount : public IAccount, public BalanceNotifier, public BankProduct
{
public:
	DebitAccount(IAccount& _account, const double & _maxDebit) :
		account(_account), debitBalans(_account.getBalance()), maxDebit(_maxDebit) {}

	virtual std::string getAccountId() const override { return account.getAccountId(); }
	virtual std::string getOwnerName() const override { return account.getOwnerName(); }
	virtual std::string getOwnerSName() const override { return account.getOwnerSName(); }
	Date::Date getCreateDate() const override { return account.getCreateDate(); }
	virtual double getBalance() const override { return debitBalans; }
	virtual void changeBalance(const double& _amount) override;
	void addToTransactionsHistory(Transaction* _t) override { account.addToTransactionsHistory(_t); }

	void accept(BankProductVisitor* _visitor) override;

private:
	IAccount& account;
	double debitBalans;
	double maxDebit;
};
class MaximumDebitUsedException : public std::exception
{
public:
	MaximumDebitUsedException(const char* _mess) : std::exception(_mess) {}
	virtual ~MaximumDebitUsedException() {}
};