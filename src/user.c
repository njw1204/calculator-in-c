#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "stack.h"
#include "flag.h"

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
  puts(" We support a range of 64-bit integers.");
  puts(" The remainder of division is discarded.");
  puts(" If you want to exit, Input 'Q'.\n");
}

void Ending() {
  printf("\n  --------------------\n");
  printf(" |   End of Program   |");
  printf("\n  --------------------\n");
  printf("\n Thank you for using our calculator! :) \n\n ");
  system("pause");
  putchar(' ');
}

int InputExp(char* dest) {
  printf(" Expression : ");
  fgets(dest, MAX_STACK - 5, stdin);
  dest[strlen(dest) - 1] = '\0';
  if (strcmp(dest, "q") == 0 || strcmp(dest, "Q") == 0) return EXIT;
  else return SUCCESS;
}

void PrintResult(long long result, int errorFlag) {
  if (errorFlag == ERROR)
    printf(" Result     : ERROR\n\n");
  else
    printf(" Result     : %lld\n\n", result);
}