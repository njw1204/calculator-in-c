#include "calc.h"
#include "flag.h"

CalcStack stack, stack2, stack3;
int weight[128];

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

static int ConvertToPostfix(const CalcData* exp, CalcStack* mainStack, CalcStack* opStack) {
  for (int i = 0; exp[i].type; i++) {
    if (exp[i].type == NUM)
      push(mainStack, exp[i]);
    else {
      if (exp[i].op == '(')
        push(opStack, exp[i]);
      else if (exp[i].op == ')') {
        int pass = 0;
        while (size(opStack)) {
          CalcData t = pop(opStack);
          if (t.op == '(') {
            pass = 1;
            break;
          }
          else
            push(mainStack, t);
        }
        if (!pass)
          return ERROR;
      }
      else {
        while (size(opStack) && weight[top(opStack).op] >= weight[exp[i].op])
          push(mainStack, pop(opStack));
        push(opStack, exp[i]);
      }
    }
  }

  while (size(opStack)) {
    CalcData t = pop(opStack);
    if (t.op == '(')
      return ERROR;
    push(mainStack, t);
  }

  return SUCCESS;
}

int CalculatePostfix(CalcStack* srcStack, CalcStack* supportStack, long long* result) {
  while (size(srcStack)) {
    CalcData t = pop(srcStack), a, b;
    if (t.type == OP) {
      switch (t.op) {
      case '+': case '-': case '*': case '/':
        if (size(supportStack) < 2) return ERROR;
        b = pop(supportStack), a = pop(supportStack);
        break;
      case 'm':
        if (size(supportStack) < 1) return ERROR;
        a = pop(supportStack);
        break;
      default:
        return ERROR;
      }
      if (t.op == '+') a.num += b.num;
      else if (t.op == '-') a.num -= b.num;
      else if (t.op == '*') a.num *= b.num;
      else if (t.op == '/') {
        if (b.num == 0) return ERROR;
        a.num /= b.num;
      }
      else if (t.op == 'm') a.num = -a.num;
      push(supportStack, a);
    }
    else {
      push(supportStack, t);
    }
  }
  
  if (size(supportStack) != 1 || top(supportStack).type != NUM)
    return ERROR;

  *result = pop(supportStack).num;
  return SUCCESS;
}

int CalcExp(const CalcData* exp, long long* result) {
  Init();

  if (ConvertToPostfix(exp, &stack, &stack2) == ERROR)
    return ERROR;

  while (size(&stack))
    push(&stack3, pop(&stack));

  return CalculatePostfix(&stack3, &stack, result);
}