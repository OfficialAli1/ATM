

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "util.h"







// Function to create a new user node
struct User* create_user(int id, const char *username, int *password, float balance) 
{
    struct User *new_user = (struct User*)malloc(sizeof(struct User));
    if (new_user == NULL) 
	{
        printf("Memory allocation failed");
        return NULL;
    }
	new_user->user_id=id;
    strcpy(new_user->username, username);
	int concatenated_password=concatenate_array(password,4);
    new_user->password=concatenated_password;
	new_user->current_balance=balance;
    new_user->next = NULL;
    return new_user;
}
// Function to load users from the CSV file into the linked list
struct User* load_users(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        return NULL;
    }

    struct User *head = NULL;
    struct User *tail = NULL;
    char line[100];
    fgets(line, sizeof(line), file);  // Skip the header

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        int id, password;
        char username[50];
        float balance;

        // Parse each field
        if (sscanf(line, "%d,%[^,],%d,%f", &id, username, &password, &balance)) {
            struct User *new_user = (struct User*)malloc(sizeof(struct User));
            if (!new_user) {
                printf("Memory allocation failed\n");
                fclose(file);
                return NULL;
            }

            new_user->user_id = id;
            strcpy(new_user->username, username);
            new_user->password = password;  // Store encrypted password directly
            new_user->current_balance = balance;
            new_user->next = NULL;

            if (!head) {
                head = new_user;
                tail = new_user;
            } else {
                tail->next = new_user;
                tail = new_user;
            }
        }
    }

    fclose(file);
    return head;
}


// Function to validate user credentials against the linked list
struct User* authenticate_user(struct User *head, const char *username, int password) 
{
    struct User *current = head;
    while (current != NULL) 
	{
        if (strcmp(current->username, username) == 0 && current->password== password) 
		{
            return current;  // Authentication successful
        }
        current = current->next;
    }
    return NULL;  // Authentication failed
}



// Function to free the linked list
void free_users(struct User *head) 
{
    struct User *temp;
    while (head != NULL) 
	{
        temp = head;
        head = head->next;
        free(temp);
    }
}