#include "transaction.hpp"

void Transaction::undo()
{
	if (!executed)
	{
		throw TansactionStateException("transaction wasn't executed");
	}
	executed = false;
}

void Transaction::execute()
{
	if (invalid)
	{
		throw InvalidTansactionException("transaction is invalid");
	}
	if (executed)
	{
		throw TansactionStateException("transaction was executed");
	}
	executed = true;
}