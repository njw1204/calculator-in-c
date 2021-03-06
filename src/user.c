#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "stack.h"
#include "flag.h"

static void cls();

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
  puts(" We can calculate the whole expression even which includes parentheses.");
  puts(" Support big integers between -10^5000 and 10^5000.");
  puts(" The remainder of division is discarded.");
  puts(" Input 'exit' to end, 'clear' to reset the screen.\n\n");
}

void Ending() {
  printf("\n --------------------\n");
  printf(" |  End of Program  |");
  printf("\n --------------------\n");
  printf("\n Thank you for using our calculator! :) \n\n ");
#ifdef _WIN32
  system("pause");
  putchar(' ');
#endif
}

int InputExp(char* dest) {
  printf(" > ");
  memset(dest, 0, MAX_STACK);
  fgets(dest, MAX_STACK, stdin);
  if (dest[MAX_STACK - 1] != '\0') strcpy(dest, "E");
  else dest[strlen(dest) - 1] = '\0';
  if (strcmp(dest, "exit") == 0) return EXIT;
  else if (strcmp(dest, "clear") == 0) {
    cls();
    return CLEAR;
  }
  else return SUCCESS;
}

void PrintResult(BigInt* result) {
  if (result == NULL) {
    printf(" = ERROR\n\n");
    return;
  }
  char num[BIGINT_SIZE];
  Get(result, num);
  printf(" = %s\n\n", num);
}

static void cls() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}