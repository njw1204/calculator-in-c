#include <string.h>
#include "calc.h"
#include "flag.h"

CalcStack stack, stack2, stack3;
static int weight[128];

static void Init() {
  weight['('] = 1;
  weight['+'] = 2;
  weight['-'] = 2;
  weight['*'] = 3;
  weight['/'] = 3;
  weight['m'] = 4;
  clear(&stack);
  clear(&stack2);
  clear(&stack3);
}

static int ConvertToPostfix(const CalcData* expr, CalcStack* mainStack, CalcStack* opStack) {
  for (int i = 0; expr[i].type; i++) {
    if (expr[i].type == NUM)
      push(mainStack, &expr[i]);
    else {
      if (expr[i].op == '(')
        push(opStack, &expr[i]);
      else if (expr[i].op == ')') {
        int pass = 0;
        while (size(opStack)) {
          CalcData t;
          memcpy(&t, pop(opStack), sizeof(CalcData));
          if (t.op == '(') {
            pass = 1;
            break;
          }
          else
            push(mainStack, &t);
        }
        if (!pass)
          return ERROR;
      }
      else {
        while (size(opStack) && weight[top(opStack)->op] >= weight[expr[i].op])
          push(mainStack, pop(opStack));
        push(opStack, &expr[i]);
      }
    }
  }

  while (size(opStack)) {
    CalcData t;
    memcpy(&t, pop(opStack), sizeof(CalcData));
    if (t.op == '(')
      return ERROR;
    push(mainStack, &t);
  }

  return SUCCESS;
}

int CalculatePostfix(CalcStack* srcStack, CalcStack* supportStack, BigInt* result) {
  while (size(srcStack)) {
    CalcData t, a, b;
    memcpy(&t, pop(srcStack), sizeof(CalcData));

    if (t.type == OP) {
      switch (t.op) {
      case '+': case '-': case '*': case '/':
        if (size(supportStack) < 2) return ERROR;
        memcpy(&b, pop(supportStack), sizeof(CalcData));
        memcpy(&a, pop(supportStack), sizeof(CalcData));
        break;
      case 'm':
        if (size(supportStack) < 1) return ERROR;
        memcpy(&a, pop(supportStack), sizeof(CalcData));
        break;
      default:
        return ERROR;
      }

      if (t.op == '+') {
        if (Add(&a.num, &b.num) == ERROR) return ERROR;
      }
      else if (t.op == '-') {
        if (Sub(&a.num, &b.num) == ERROR) return ERROR;
      }
      else if (t.op == '*') {
        if (Mul(&a.num, &b.num) == ERROR) return ERROR;
      }
      else if (t.op == '/') {
        if (Div(&a.num, &b.num) == ERROR) return ERROR;
      }
      else if (t.op == 'm') {
        if (a.num.sign == -1) a.num.sign = 1;
        else a.num.sign = -1;
      }

      push(supportStack, &a);
    }
    else push(supportStack, &t);
  }

  if (size(supportStack) != 1 || top(supportStack)->type != NUM)
    return ERROR;

  Copy(result, &top(supportStack)->num);
  return SUCCESS;
}

int CalcExp(const CalcData* expr, BigInt* result) {
  Init();

  if (ConvertToPostfix(expr, &stack, &stack2) == ERROR)
    return ERROR;

  while (size(&stack))
    push(&stack3, pop(&stack));

  return CalculatePostfix(&stack3, &stack, result);
}