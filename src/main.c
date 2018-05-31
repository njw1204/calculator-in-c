#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char expRaw[MAX_STACK - 5];
CalcData exp[MAX_STACK - 5];

int main() {
  int errorFlag;
  long long result;

  Intro();

  while (1) {
    if (InputExp(expRaw) == 0) break;
    errorFlag = ExpParse(expRaw, exp, sizeof(exp));
    errorFlag = CalcExp(exp, &result);
    PrintResult(result, errorFlag);
  }

  Ending();

  return 0;
}

void Ending() {
	printf("\n  --------------------\n");
	printf(" |   End of Program   |");
	printf("\n  --------------------\n");

	printf("\n Thank you for using our calculator! :) \n\n ");
  system("pause");
  putchar(' ');
}