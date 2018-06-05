#pragma once
#include "bigint.h"
#define MAX_STACK 100005

enum TYPE { OP = 1, NUM = 2 };

typedef struct CalcData {
  int type;
  char op;
  long long num;
} CalcData;

typedef struct CalcStack {
  int top;
  CalcData data[MAX_STACK];
} CalcStack;

void push(CalcStack* stack, CalcData val);
CalcData pop(CalcStack* stack);
CalcData top(const CalcStack* stack);
int size(const CalcStack* stack);
void clear(CalcStack* stack);