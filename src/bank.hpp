#pragma once

#include "iaccount.hpp"
#include "account.hpp"
#include "debitaccount.hpp"
#include "deposit.hpp"
#include "loan.hpp"
#include "cardpayment.hpp"
#include "payment.hpp"
#include "balancelistener.hpp"
#include "deposittransactions.hpp"
#include "loantransactions.hpp"

#include <list>
#include <optional>

class BankProductVisitor;

class Bank
{
public:

	static Bank* createBank(const std::string& _bankName);
	~Bank();

	Account* createAccount(const std::string& _ownerName, const std::string& _ownerSName);
	DebitAccount* createDebitAccount(const std::string& _ownerName, const std::string& _ownerSName,
		const double _maxDebit);

	void depositMoney(IAccount& _account, double _amount);
	void takeLoan(IAccount& _account, double _amount);

	void makePayment(Payment& p);
	void makeCardPayment(CardPayment& p);
	void closeDeposit(CloseDepositTransaction & cd);
	void payLoan(PayLoanTransaction& pl);
	void addToTransactionsHistory(Transaction* _t);

	const std::string& getBankId() const { return bankId; }
	std::optional<IAccount*> getAccount(std::string _id);

	std::string createBalanceRaport();
	std::string createCreateDateRaport();

protected:
	Bank(const std::string& _bankId);

private:
	std::list<Account*> accounts;
	std::list<DebitAccount*> debAccounts;
	std::list<Card*> cards;
	std::list<Deposit*> deposits;
	std::list<Loan*> loans;
	std::list<Transaction*> historyOfTransactions;

	const std::string bankId;
	DebitAccount* bankAccount;

	void makeReport(BankProductVisitor* _visitor);
	unsigned int getNextAccountId() { return ++nextAccountId; }

	BalanceListenerRaport1000Up* balanceChangeUp1000L;
	unsigned int nextAccountId;
};