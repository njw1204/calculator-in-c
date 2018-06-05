#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "bigint.h"
#include "flag.h"

char tempNumStr[MAX_STACK - 5];

int ExpParse(char* expRaw, CalcData* expDest, size_t expDestSize) {
  int tempStrPos = 0, outPos = 0;
  memset(tempNumStr, 0, sizeof(tempNumStr));
  memset(expDest, 0, expDestSize);

  for (size_t i = 0; i < strlen(expRaw); i++) {
    if (expRaw[i] == ' ' || expRaw[i] == '\t')
      continue;

    else if (expRaw[i] >= '0' && expRaw[i] <= '9')
      tempNumStr[tempStrPos++] = expRaw[i];

    else if (expRaw[i] == '+' || expRaw[i] == '-' ||
      expRaw[i] == '*' || expRaw[i] == '/' ||
      expRaw[i] == '(' || expRaw[i] == ')') {

      if (tempStrPos) {
        CalcData x;
        x.type = NUM;
        x.op = -1;
		Set(&x.num, tempNumStr);
        expDest[outPos++] = x;
        memset(tempNumStr, 0, sizeof(tempNumStr));
        tempStrPos = 0;
      }

      if ((expRaw[i] == '+' || expRaw[i] == '-') && (outPos == 0 || expDest[outPos - 1].op == '(')) {
        if (expRaw[i] == '-') expRaw[i] = 'm';
        else continue;
      }
      else if (expRaw[i] != '(' && outPos > 0 && expDest[outPos - 1].type == OP && expDest[outPos - 1].op != ')')
        return ERROR;

      CalcData x;
      x.type = OP;
      x.op = expRaw[i];
      expDest[outPos++] = x;
    }

    else
      return ERROR;
  }

  if (tempStrPos) {
    CalcData x;
    x.type = NUM;
    x.op = -1;
	Set(&x.num, tempNumStr);
    expDest[outPos++] = x;
    memset(tempNumStr, 0, sizeof(tempNumStr));
    tempStrPos = 0;
  }

  return SUCCESS;
}