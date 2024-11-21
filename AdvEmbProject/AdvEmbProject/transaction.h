#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include "user.h"


typedef struct Transaction
{
	int transaction_id;
	char transaction_type;
	float amount;
	int user_id;
	struct Transaction *next;
}Transaction;

void Record_Transaction(int user_id, char transaction_type, float amount);

void Balance_Inquiry(User *user);

void Deposit_Funds(User *user,float amount_deposit);

void Withdraw_Funds(User *user,float amount_withdraw);

void Transaction_History(int user_id);









#endif