#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "parse.h"
#include "user.h"

char expRaw[100000];
CalcData exp[100000];

int main() {
  while (1) {
    if (UserInterface(expRaw) == 0) break;
  }
  system("pause");
  return 0;
}