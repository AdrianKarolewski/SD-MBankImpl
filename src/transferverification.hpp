#pragma once

#include "payment.hpp"
#include "cardpayment.hpp"

class TransferVerification
{
public:
	static void verifyPayment(Payment& _payment);
	static void verifyCardPayment(CardPayment& _cardPayment);
};