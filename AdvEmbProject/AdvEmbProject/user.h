#ifndef USER_H_
#define USER_H_



typedef struct User
{
	int user_id;
	char username[50];
	int password;
	float current_balance;
	struct User *next;
}User;

struct User* create_user(int id, const char *username, int *password, float balance);

struct User* load_users(const char *filename);

struct User* authenticate_user(struct User *head, const char *username, int password);

void free_users(struct User *head);







#endif