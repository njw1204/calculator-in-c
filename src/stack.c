#include <string.h>
#include "stack.h"
#include "flag.h"

void push(CalcStack* stack, const CalcData* val) {
  memcpy(&stack->data[(stack->top)++], val, sizeof(CalcData));
}

CalcData* pop(CalcStack* stack) {
  if (stack->top == 0) return NULL;
  return &stack->data[--(stack->top)];
}

CalcData* top(CalcStack* stack) {
  if (stack->top == 0) return NULL;
  return &stack->data[stack->top - 1];
};

int size(const CalcStack* stack) {
  return stack->top;
}

void clear(CalcStack* stack) {
  stack->top = 0;
}