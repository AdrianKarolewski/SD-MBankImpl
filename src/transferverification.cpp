#include "transferverification.hpp"
#include "interbankpayment.hpp"

void TransferVerification::verifyPayment(Payment& _payment)
{
    if (!(_payment.fromAccount.getBalance() >= _payment.amount
        && InterBankPayment::get()->findAccount(_payment.fromAccount.getAccountId())
        && InterBankPayment::get()->findAccount(_payment.toAccount.getAccountId())))

        _payment.setInvalid();
}

void TransferVerification::verifyCardPayment(CardPayment& _cardPayment)
{
    if (!(_cardPayment.fromCard.assignedAccount.getBalance() >= _cardPayment.amount
        && InterBankPayment::get()->findAccount(_cardPayment.fromCard.assignedAccount.getAccountId())
        && InterBankPayment::get()->findAccount(_cardPayment.toAccount.getAccountId())))

        _cardPayment.setInvalid();
}