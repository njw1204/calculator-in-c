#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char expRaw[MAX_STACK - 5];
CalcData exp[MAX_STACK - 5];

int main() {
  int errorFlag;
  long long result;

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