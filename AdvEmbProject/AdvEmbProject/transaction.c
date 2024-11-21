



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"





// Function to record a transaction in the CSV file
void Record_Transaction(int user_id, char transaction_type, float amount) 
{
    FILE *file = fopen("transactions.csv", "a");
    if (!file) 
    {
        perror("Could not open transactions file");
        return;
    }
    // Generate a transaction ID (in a real application, this would be more complex)
    static int transaction_id = 1;
    fprintf(file,"%d,%d,%c,%.2f\n",transaction_id++,user_id,transaction_type,amount);
    fclose(file);
}

//function to check and print the user's current balance
void Balance_Inquiry(User *user)
{
    printf("Your current balance is: %.2f\n",user->current_balance);
}
// Function to deposit funds and update the user's balance
void Deposit_Funds(User *user,float amount_deposit)
{
	if(amount_deposit>0)
	{
		user->current_balance += amount_deposit;
		printf("Deposit is successful and new balance is : %.2f\n",user->current_balance);
		Record_Transaction(user->user_id, 'D', amount_deposit);
	}
	else
	{
		printf("invalid deposit amount\n");
	}
}
//function to withdraw funds
void Withdraw_Funds(User *user,float amount_withdraw)
{
	if(amount_withdraw>0 && amount_withdraw<=user->current_balance)
	{
		user->current_balance -=amount_withdraw;
		printf("withdraw is successful and your current balance is: %.2f\n",user->current_balance);
		Record_Transaction(user->user_id, 'W', amount_withdraw);
	}
	else
	{
		printf("insufficient amount of money to deposit or invalid amount\n");
	}
}
// Function to view transaction history for a specific user
void Transaction_History(int user_id) 
{
    FILE *file = fopen("transactions.csv", "r");
    if (!file) 
    {
        perror("Could not open transactions file");
        return;
    }
    char line[100];
    int transaction_id, tid_user_id;
    char transaction_type;
    float amount;
    printf("Transaction History:\n");
    printf("ID\tType\tAmount\n");
	// Skip the header line
    fgets(line, sizeof(line), file);
    // Read each line in the CSV file
    while (fgets(line, sizeof(line), file)) 
    {
        if (sscanf(line, "%d,%d,%c,%f", &transaction_id, &tid_user_id, &transaction_type, &amount) == 4) 
        {
            if (tid_user_id == user_id) 
            {
                printf("%d\t%c\t%.2f\n", transaction_id, transaction_type, amount);
            }
        }
    }
    fclose(file);
}