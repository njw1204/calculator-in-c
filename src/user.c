#include "user.h"u

void Intro() {
	printf("You don't need make a calculation one by one!\n");
	printf("We can calculate the whole expression even which includes parenthesis.\n\n");
}

int InputExp(char* dest) {
	printf("Write your expression to calculate: ");
	fgets(dest, 100000, stdin);
	dest[strlen(dest) - 1] = '\0';
}

void PrintResult(long long result) {
	printf("Calculating.....\n");
	printf("Please wait for a second.\n");
	printf("The result of your experession is %lld.\n\n", result);
	
}

