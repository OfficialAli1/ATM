#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "transaction.h"
#include "util.h"







int main()
{
	char username[50];
	int password,pass[4],encrypted_pass[4],temp_val; 
	int wrong_pass=1;
	const char *filename = "users.csv";
	// Load users from the CSV file into a linked list
    struct User *users = load_users(filename);
    if (users == NULL) 
	{
        printf("Failed to load users.\n");
        return -1;
    }
	User *authenticated_user = NULL;
	int choice,exit=0;
	while(!exit)
	{
		printf("please enter\n1. to enter the ATM system\n2. to exit the ATM\n");
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:
			{
				printf("Welcome to the ATM system\n");	
				while(wrong_pass)
				{
					printf("please enter the username: ");
					scanf("%s",username);
					printf("please enter the password: ");
					scanf("%d",&temp_val);
					split_number_into_array(temp_val,pass,4);
					encryption(pass,encrypted_pass);
					password=concatenate_array(encrypted_pass,4);
					
					
					authenticated_user = authenticate_user(users, username, password);
					if (authenticated_user != NULL)			
					{
						printf("Hello %s, welcome to the ATM system!\n", authenticated_user->username);
						wrong_pass=0;
					} 
					else 
					{
						printf("Invalid username or password.\n");
						wrong_pass=1;
					}
				}
				wrong_pass=1;
				int option, cont=1;
				while(cont)
				{
					printf("please enter one of the following options\n");
					printf("1. Balance inquiry\n2. Deposit Funds\n3. Withdraw Funds\n4. View Transaction history\n5. Exit\n");
					scanf("%d",&option);
					switch(option)
					{
						case 1:
						{
							Balance_Inquiry(authenticated_user);
							break;
						}
						case 2:
						{
							float amount_deposit;
							printf("enter amount to deposit: ");
							scanf("%f",&amount_deposit);
							Deposit_Funds(authenticated_user,amount_deposit);
							break;
						}
						case 3:
						{
							float amount_withdraw;
							printf("enter amount to withdraw: ");
							scanf("%f",&amount_withdraw);
							Withdraw_Funds(authenticated_user,amount_withdraw);
							break;
						}
						case 4:
						{
							Transaction_History(authenticated_user->user_id);
							break;
						}
						case 5:
						{
							cont=0;
							break;
						}
						default:
						{
							printf("invalid input!");
							break;
						}
					}
				}
				break;
			}
			case 2:
			{
				exit=1;
				printf("thank you for using the ATM system\n");
				break;
			}
			default:
			{
				printf("invalid input!");
				break;
			}
		}
	}
	free_users(users);
	return 0;
}