#include "interbankpayment.hpp"
#include "transferverification.hpp"

InterBankPayment* InterBankPayment::get()
{
	static InterBankPayment* ptr = new InterBankPayment();
	return ptr;
}

void InterBankPayment::registerBank(Bank* _bank)
{
	registeredBanks.push_back(_bank);
}

void InterBankPayment::unregisterBank(Bank* _bank)
{
	auto it = std::find_if(registeredBanks.begin(), registeredBanks.end(), [_bank](const Bank* b) {
		return b->getBankId() == _bank->getBankId();
		});
	if(it != registeredBanks.end())
		registeredBanks.erase(it);
}

void InterBankPayment::makeInterBankPayment(Payment& _p)
{
	TransferVerification::verifyPayment(_p);

	_p.execute();
	auto ptrCP = new Payment(_p);

	_p.fromAccount.addToTransactionsHistory(ptrCP);
	_p.toAccount.addToTransactionsHistory(ptrCP);
}

void InterBankPayment::makeInterBankCardPayment(CardPayment& _cp)
{
	TransferVerification::verifyCardPayment(_cp); // sprawdzi czy konta istnieja i czy kasa jest ok

	_cp.execute();
	auto ptrCP = new CardPayment(_cp);

	_cp.fromCard.assignedAccount.addToTransactionsHistory(ptrCP);
	_cp.toAccount.addToTransactionsHistory(ptrCP);
}

std::optional<IAccount*> InterBankPayment::findAccount(std::string _id)
{
	for (auto bank : registeredBanks)
	{
		if (auto account = bank->getAccount(_id))
		{
			return account;
		}
	}
	return {};
}