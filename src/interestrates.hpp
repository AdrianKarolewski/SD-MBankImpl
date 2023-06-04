#pragma once

class IAccount;
class Loan;
class Deposit;

class IInterrates
{
public:
	virtual double calculateRates() = 0;
	virtual ~IInterrates() {}
};

class LoanInterrates : public IInterrates
{
public:
	LoanInterrates(Loan& _loan) : loan(_loan) {}
	double calculateRates() override;
private:
	Loan& loan;
};

class PremiumLoanInterrates : public IInterrates
{
public:
	PremiumLoanInterrates(Loan& _loan) : loan(_loan) {}
	double calculateRates() override;
private:
	Loan& loan;
};

class AccountInterrates : public IInterrates
{
public:
	AccountInterrates(IAccount& _account) : account(_account) {}
	double calculateRates() override;
private:
	IAccount& account;
};

class PremiumAccountInterrates : public IInterrates
{
public:
	PremiumAccountInterrates(IAccount& _account) : account(_account) {}
	double calculateRates() override;
private:
	IAccount& account;
};


class DepositInterrates : public IInterrates
{
public:
	DepositInterrates(Deposit& _deposit) : deposit(_deposit) {}
	double calculateRates() override;
private:
	Deposit& deposit;
};

class PremiumDepositInterrates : public IInterrates
{
public:
	PremiumDepositInterrates(Deposit& _deposit) : deposit(_deposit) {}
	double calculateRates() override;
private:
	Deposit& deposit;
};