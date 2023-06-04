#pragma once

#include "iaccount.hpp"
#include <string>

class Transaction
{
public:
	Transaction() : executed(false), invalid(false) {}
	virtual ~Transaction() {}
	virtual void undo();
	virtual void execute();
	bool wasExecuted() { return executed; }
	bool isInvalid() { return invalid; }
	void setInvalid() { invalid = true; }
private:
	bool invalid;
	bool executed;
};

class InvalidTansactionException : public std::exception
{
public:
	InvalidTansactionException(const char* _mess) : std::exception(_mess) {}
	virtual ~InvalidTansactionException() {}
};
class TansactionStateException : public std::exception
{
public:
	TansactionStateException(const char* _mess) : std::exception(_mess) {}
	virtual ~TansactionStateException() {}
};
class InvalidAmountException : public std::exception
{
public:
	InvalidAmountException(const char* _mess) : std::exception(_mess) {}
	virtual ~InvalidAmountException() {}
};