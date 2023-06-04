#include "bank.hpp"
#include "interbankpayment.hpp"
#include "debitaccount.hpp"
#include "account.hpp"
#include "reporting.hpp"


Bank* Bank::createBank(const std::string& _bankId)
{
	Bank* newBank = new Bank(_bankId);
	InterBankPayment::get()->registerBank(newBank);

	AccountBuilder builder;
	Account* account = new Account(builder
		.accountId(_bankId)
		.ownerName("bank")
		.ownerSName("bank")
		.balance(0));

	newBank->bankAccount = new DebitAccount(*account, 1000000);
	return newBank;
}
Bank::Bank(const std::string& _bankId) : bankId(_bankId), bankAccount(nullptr),
balanceChangeUp1000L(new BalanceListenerRaport1000Up()), nextAccountId(0)
{

}
Bank::~Bank()
{
	InterBankPayment::get()->unregisterBank(this);
	delete bankAccount;
}

Account* Bank::createAccount(const std::string& _ownerName, const std::string& _ownerSName)
{
	AccountBuilder builder;
	Account* account = new Account(builder
		.accountId(bankId + "A" + std::to_string(getNextAccountId()))
		.ownerName(_ownerName)
		.ownerSName(_ownerSName)
		.createDate(Date::currentDate())
		.balance(0));
	account->subscribe(balanceChangeUp1000L);
	accounts.push_back(account);
	return account;
}

DebitAccount* Bank::createDebitAccount(const std::string& _ownerName, const std::string& _ownerSName,
	const double _maxDebit)
{
	AccountBuilder builder;
	Account* account = new Account(builder
		.accountId(bankId + "D" + std::to_string(getNextAccountId()))
		.ownerName(_ownerName)
		.ownerSName(_ownerSName)
		.createDate(Date::currentDate())
		.balance(0));
	account->subscribe(balanceChangeUp1000L);

	DebitAccount* dAccount = new DebitAccount(*account, _maxDebit);
	dAccount->subscribe(balanceChangeUp1000L);
	debAccounts.push_back(dAccount);
	return dAccount;
}

void Bank::depositMoney(IAccount& _account, double _amount)
{
	auto newDeposit = new Deposit(_account, _amount);
	auto dmTransaction = new DepositMoneyTransaction(*newDeposit, "");
	dmTransaction->execute();
	historyOfTransactions.emplace_front(dmTransaction);
	_account.addToTransactionsHistory(dmTransaction);
	if (!dmTransaction->isInvalid())
	{
		deposits.push_back(newDeposit);
	}
}

void Bank::takeLoan(IAccount& _account, double _amount)
{
	auto newLoan = new Loan(_account, _amount);
	auto tlTransaction = new TakeLoanTransacion(*newLoan, "");
	tlTransaction->execute();
	historyOfTransactions.emplace_front(tlTransaction);
	_account.addToTransactionsHistory(tlTransaction);
	if (!tlTransaction->isInvalid())
	{
		loans.push_back(newLoan);
	}
}

void Bank::closeDeposit(CloseDepositTransaction& cd)
{
	cd.execute();
	auto closeDepositTrans = new CloseDepositTransaction(cd);
	historyOfTransactions.emplace_front(closeDepositTrans);
	closeDepositTrans->deposit.getAssignedAccount().addToTransactionsHistory(closeDepositTrans);
}

void Bank::payLoan(PayLoanTransaction& pl)
{
	pl.execute();
	auto payLoanTrans = new PayLoanTransaction(pl);
	historyOfTransactions.emplace_front(payLoanTrans);
	payLoanTrans->loan.getAssignedAccount().addToTransactionsHistory(payLoanTrans);
}

void Bank::addToTransactionsHistory(Transaction* _t)
{
	historyOfTransactions.emplace_front(_t);
}

void Bank::makePayment(Payment& p)
{

	auto fromAccount = getAccount(p.fromAccount.getAccountId());
	if (!fromAccount) // nie ma tego konta w banku
	{
		InterBankPayment::get()->makeInterBankPayment(p);
		auto ptrP = new Payment(p);
		addToTransactionsHistory(ptrP);
		return;
	}
		

	auto toAccount = getAccount(p.toAccount.getAccountId());
	if (!toAccount)
	{
		InterBankPayment::get()->makeInterBankPayment(p);
		auto ptrP = new Payment(p);
		addToTransactionsHistory(ptrP);
		return;
	}
	p.execute();
	auto ptrP = new Payment(p);
	addToTransactionsHistory(ptrP);
	fromAccount.value()->addToTransactionsHistory(ptrP);
	toAccount.value()->addToTransactionsHistory(ptrP);

}

void Bank::makeCardPayment(CardPayment& cp)
{
	auto fromAccount = getAccount(cp.fromCard.assignedAccount.getAccountId());
	if (!fromAccount) // nie ma tego konta w banku
	{
		InterBankPayment::get()->makeInterBankCardPayment(cp);
		auto ptrCP = new CardPayment(cp);
		addToTransactionsHistory(ptrCP);
		return;
	}

	auto toAccount = getAccount(cp.toAccount.getAccountId());
	if (!toAccount)
	{
		InterBankPayment::get()->makeInterBankCardPayment(cp);
		auto ptrCP = new CardPayment(cp);
		addToTransactionsHistory(ptrCP);
		return;
	}
	cp.execute();
	auto ptrCP = new CardPayment(cp);
	addToTransactionsHistory(ptrCP);
	fromAccount.value()->addToTransactionsHistory(ptrCP);
	toAccount.value()->addToTransactionsHistory(ptrCP);
}

std::optional<IAccount*> Bank::getAccount(std::string _id)
{
	{
		auto it = std::find_if(accounts.begin(), accounts.end(), [_id](const Account* a) {
			return a->getAccountId() == _id;
			});

		if (it != accounts.end())
			return *it;
	}
	{
		auto it = std::find_if(debAccounts.begin(), debAccounts.end(), [_id](const DebitAccount* d) {
			return d->getAccountId() == _id;
			});

		if (it != debAccounts.end())
			return *it;
	}

	return {};
}

std::string Bank::createBalanceRaport()
{
	BalanceReport* reporter = new BalanceReport();
	makeReport(reporter);

	auto s = reporter->getRaport();
	delete reporter;
	return s;
}

std::string Bank::createCreateDateRaport()
{
	CreateDateReport* reporter = new CreateDateReport();
	makeReport(reporter);

	auto s = reporter->getRaport();
	delete reporter;
	return s;
}



void Bank::makeReport(BankProductVisitor* _visitor)
{
	for (auto& a : accounts)
		a->accept(_visitor);
	for (auto& d : debAccounts)
		d->accept(_visitor);
	for (auto& l : loans)
		l->accept(_visitor);
	for (auto& d : deposits)
		d->accept(_visitor);
}