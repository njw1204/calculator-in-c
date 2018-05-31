#include <stdio.h>
#include "main.h"

char expRaw[MAX_STACK - 5];
CalcData exp[MAX_STACK - 5];

int main() {
  int errorFlag = SUCCESS;
  long long result = 0;

  Intro();

  while (1) {
    if (InputExp(expRaw) == EXIT) break;
    errorFlag = ExpParse(expRaw, exp, sizeof(exp));
    if (errorFlag == SUCCESS) errorFlag = CalcExp(exp, &result);
    PrintResult(result, errorFlag);
  }

  Ending();

  return 0;
}