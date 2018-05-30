#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "parse.h"
#include "user.h"

char expRaw[100000];
CalcData exp[100000];

int main() {
  while (1) {
    if (InputExp(expRaw) == 0) break;
	ExpParse(expRaw, exp);
	PrintResult(CalcExp(exp));
  }
  system("pause");
  return 0;
}