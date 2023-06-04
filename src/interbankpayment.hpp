#pragma once
#include "bank.hpp"
#include <list>

class InterBankPayment
{
public:
	static InterBankPayment* get();
	void registerBank(Bank* _bank);
	void unregisterBank(Bank* _bank);
	void makeInterBankPayment(Payment& _transaction);
	void makeInterBankCardPayment(CardPayment& _transaction);
	std::optional<IAccount*> findAccount(std::string _id);
	

protected:
	InterBankPayment() {}
private:

	std::list<Bank*> registeredBanks;

	InterBankPayment(const InterBankPayment&) = delete;
	InterBankPayment(InterBankPayment&&) = delete;
	InterBankPayment& operator=(const InterBankPayment&) = delete;
	InterBankPayment& operator=(InterBankPayment&&) = delete;
};