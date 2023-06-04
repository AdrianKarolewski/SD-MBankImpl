#pragma once
#include <string>
#include "utils.hpp"

class Transaction;

class IAccount
{
public:
	virtual std::string getAccountId() const = 0;
	virtual std::string getOwnerName() const = 0;
	virtual std::string getOwnerSName() const = 0;
	virtual Date::Date getCreateDate() const = 0;
	virtual double getBalance() const = 0;
	virtual void changeBalance(const double& _amount) = 0;
	virtual void addToTransactionsHistory(Transaction* _t) = 0;
	virtual ~IAccount() {}
};