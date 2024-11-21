


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encryption(int *password,int *encrypted_pass){
	
	int key[2][2]={{3,2},
		{5,7}};
	encrypted_pass[0]=(password[0]*key[0][0]+password[0]*key[0][1])%10;
	encrypted_pass[1]=(password[1]*key[1][0]+password[1]*key[1][1])%10;
	encrypted_pass[2]=(password[2]*key[0][0]+password[2]*key[0][1])%10;
	encrypted_pass[3]=(password[3]*key[1][0]+password[3]*key[1][1])%10;
	
}
int concatenate_array(int *array, int size) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        result = result * 10 + array[i]; // Shift the current digits left and add the next digit
    }

    return result;
}

void split_number_into_array(int number, int *array, int size) {
    for (int i = size - 1; i >= 0; i--) {
        array[i] = number % 10; // Extract the last digit
        number /= 10;           // Remove the last digit
    }
}