#pragma once
#include <list>

#include "balancenotifier.hpp"
#include "reportingproduct.hpp"
#include "iaccount.hpp"
#include "utils.hpp"

class Transaction;

class Account : public IAccount, public BalanceNotifier, public BankProduct
{
public:
	~Account() {}
	std::string getAccountId()  const override { return accountId; }
	std::string getOwnerName() const override { return ownerName; }
	std::string getOwnerSName() const override { return ownerSName; }
	Date::Date getCreateDate() const override { return createDate; }

	double getBalance() const override { return balance; }
	void changeBalance(const double& _amount) override;
	void addToTransactionsHistory (Transaction* _t) override;

	void accept(BankProductVisitor* _visitor) override;

private:
	Account() : accountId(""), balance(0), createDate({ 0,0,0 }) {}

	std::string accountId;
	std::string ownerName;
	std::string ownerSName;
	double balance;
	Date::Date createDate;

	friend class AccountBuilder;

	std::list<Transaction*> historyOfTransactions;
};

class NotEnoughtMoneyException : public std::exception
{
public:
	NotEnoughtMoneyException(const char * _mess) : std::exception(_mess) {}
	virtual ~NotEnoughtMoneyException() {}
};

class AccountBuilder
{
public:
	AccountBuilder() {};
	operator Account() { return account; }
	Account build() { return account; }
	AccountBuilder& accountId(const std::string& _id) { account.accountId = _id; return *this; }
	AccountBuilder& ownerName(const std::string& _name) { account.ownerName = _name; return *this; }
	AccountBuilder& ownerSName(const std::string & _sname) { account.ownerSName = _sname; return *this;	}
	AccountBuilder& balance(const double& _balance) { account.balance = _balance; return *this;	}
	AccountBuilder& createDate(const Date::Date& _date) { account.createDate = _date; return *this; }

private:
	Account account;
};