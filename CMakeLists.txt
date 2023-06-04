cmake_minimum_required(VERSION 3.21.3)

project(SDMBank)

set (CMAKE_CXX_STANDARD 20)

SET (SRC
    src/account.cpp
	src/balancelistener.cpp
	src/balancenotifier.cpp
	src/bank.cpp
	src/cardpayment.cpp
	src/debitaccount.cpp
	src/deposit.cpp 
	src/deposittransactions.cpp
	src/interbankpayment.cpp
	src/interestrates.cpp
	src/loan.cpp
	src/loantransactions.cpp
	src/main.cpp
	src/payment.cpp
	src/reporting.cpp
	src/transaction.cpp
	src/transferverification.cpp
	src/utils.cpp
)
SET (TESTS
	tests/accounttest.cpp
	tests/banktest.cpp
	tests/debitaccounttest.cpp
	tests/paymenttest.cpp
	tests/transactiontest.cpp
)

SET (HEADERS
    src/account.hpp
	src/balancelistener.hpp
	src/balancenotifier.hpp
    src/bank.hpp
	src/cardpayment.hpp  
	src/debitaccount.hpp
	src/deposit.hpp
	src/deposittransactions.hpp
	src/iaccount.hpp
	src/interbankpayment.hpp
	src/interestrates.hpp
	src/loan.hpp
	src/loantransactions.hpp
	src/payment.hpp
	src/reporting.hpp
	src/reportingproduct.hpp
	src/transaction.hpp
	src/transferverification.hpp
	src/utils.hpp
)

include_directories( ./src/ )
find_package(Catch2 3 REQUIRED)
add_executable(bank ${SRC} ${TESTS} ${HEADERS})
target_link_libraries(bank PRIVATE Catch2::Catch2WithMain)