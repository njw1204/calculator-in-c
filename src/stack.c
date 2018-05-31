#include "stack.h"

void push(CalcStack* stack, CalcData val) {
  stack->data[(stack->top)++] = val;
}

CalcData pop(CalcStack* stack) {
  if (stack->top == 0) {
    CalcData t = {-1,-1,-1};
    return t;
  }
  return stack->data[--(stack->top)];
}

CalcData top(const CalcStack* stack) {
  if (stack->top == 0) {
    CalcData t = {-1,-1,-1};
    return t;
  }
  return stack->data[stack->top - 1];
};


int size(const CalcStack* stack) {
  return stack->top;
}

void clear(CalcStack* stack) {
  stack->top = 0;
}