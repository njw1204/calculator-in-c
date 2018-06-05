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

static int ConvertToPostfix(const CalcData* expr, CalcStack* mainStack, CalcStack* opStack) {
  for (int i = 0; expr[i].type; i++) {
    if (expr[i].type == NUM)
      push(mainStack, expr[i]);
    else {
      if (expr[i].op == '(')
        push(opStack, expr[i]);
      else if (expr[i].op == ')') {
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
        while (size(opStack) && weight[top(opStack).op] >= weight[expr[i].op])
          push(mainStack, pop(opStack));
        push(opStack, expr[i]);
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

int CalculatePostfix(CalcStack* srcStack, CalcStack* supportStack, BigInt* result) {
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

	  if (t.op == '+') Add(&a.num, &b.num);
	  else if (t.op == '-') Sub(&a.num, &b.num);
	  else if (t.op == '*') Mul(&a.num, &b.num);
    else if (t.op == '/') Div(&a.num, &b.num);
	  else if (t.op == 'm') {
		  if (a.num.sign == -1) a.num.sign = 1;
		  else a.num.sign = -1;
	  }
      push(supportStack, a);
    }

    else
      push(supportStack, t);
  }
  
  if (size(supportStack) != 1 || top(supportStack).type != NUM)
    return ERROR;

  CalcData temp = pop(supportStack);
  Copy(result, &temp.num);
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