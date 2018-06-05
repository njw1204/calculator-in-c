#include <stdio.h>
#include "main.h"

char exprRaw[MAX_STACK - 5];
CalcData expr[MAX_STACK - 5];

int main() {
  int errorFlag = SUCCESS;
  BigInt result;
  Set(&result, "0");

  Intro();

  while (1) {
    if (InputExp(exprRaw) == EXIT) break;
    errorFlag = ExpParse(exprRaw, expr, sizeof(expr));
    if (errorFlag == SUCCESS) errorFlag = CalcExp(expr, &result);
    PrintResult(result, errorFlag);
  }

  Ending();

  return 0;
}