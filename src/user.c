#include <stdio.h>
#include <string.h>
#include "user.h"
#include "stack.h"

void Intro() {
  puts("");
  puts(" _  _ _    ___ _ _  _ ____ ___ ____");
  puts(" |  | |     |  | |Ｖ| |__|  |  |___");
  puts(" |__| |___  |  | |  | |  |  |  |___");
  puts(" ____ ____ _    ____ _  _ _    ____ ___ ____ ____");
  puts(" |    |__| |    |    |  | |    |__|  |  |  | |__/ ");
  puts(" |___ |  | |___ |___ |__| |___ |  |  |  |__| |  |");
  puts("\n");
  puts(" You don't need to calculate one by one!");
  puts(" We can calculate the whole expression even which includes parenthesis.");
  puts(" Input 'Q' to exit.\n");
}

int InputExp(char* dest) {
	printf(" Expression : ");
	fgets(dest, MAX_STACK - 5, stdin);
	dest[strlen(dest) - 1] = '\0';
  if (strcmp(dest, "q") == 0 || strcmp(dest, "Q") == 0) return 0;
  else return 1;
}

void PrintResult(long long result, int error) {
  if (error)
    printf(" Result     : ERROR\n\n");
  else
  	printf(" Result     : %lld\n\n", result);
}