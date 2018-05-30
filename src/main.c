#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "parse.h"
#include "user.h"

char expRaw[100000];
CalcData exp[100000];

void Ending();

int main() {
  Intro();
  while (1) {
    if (InputExp(expRaw) == 0) break;
	  ExpParse(expRaw, exp);
	  PrintResult(CalcExp(exp));
  }
	Ending();
  system("pause");
  return 0;
}

void Ending() {
	print("\n------------------------\n");
	printf("| End of calculation |");
	print("\n------------------------\n");

	printf("\n  Thanks you for using out calculator :) \n");
}