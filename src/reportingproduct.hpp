#pragma once

class BankProductVisitor;

class BankProduct
{
public:
	virtual void accept(BankProductVisitor* _visitor) = 0;
};