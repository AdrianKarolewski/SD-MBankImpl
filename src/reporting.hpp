#pragma once

#include "account.hpp"
#include "debitaccount.hpp"
#include "loan.hpp"
#include "deposit.hpp"


class BankProductVisitor
{
public:
	virtual void visit(Account* _account) = 0;
	virtual void visit(DebitAccount* _debitAccount) = 0;
	virtual void visit(Loan* _loan) = 0;
	virtual void visit(Deposit* _deposit) = 0;
};


class BalanceReport : public BankProductVisitor
{
public:
	void visit(Account* _account) override;
	void visit(DebitAccount* _debitAccount) override;
	void visit(Loan* _loan) override;
	void visit(Deposit* _deposit) override;

	std::string getRaport() { return raport; }
private:
	std::string raport;

};
class CreateDateReport : public BankProductVisitor
{
public:
	void visit(Account* _account) override;
	void visit(DebitAccount* _debitAccount) override;
	void visit(Loan* _loan) override;
	void visit(Deposit* _deposit) override;

	std::string getRaport() { return raport; }
private:
	std::string raport;
};