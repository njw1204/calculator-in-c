#include <stdio.h>
#include "main.h"

char exprRaw[MAX_STACK];
CalcData expr[MAX_STACK];

int main() {
  BigInt result;
  int command = SUCCESS;
  for (int i = 0; i < MAX_STACK; i++) Reset(&expr[i].num);
  Reset(&result);

  while (command != EXIT) {
    Intro();
    while (1) {
      command = InputExp(exprRaw);
      if (command == EXIT) break;
      if (ExpParse(exprRaw, expr, sizeof(expr)) == SUCCESS &&
          CalcExp(expr, &result) == SUCCESS)
        PrintResult(&result);
      else
        PrintResult(NULL);
    }
  }

  Ending();
  return 0;
}