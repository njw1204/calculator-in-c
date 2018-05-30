#pragma once
enum TYPE { OP = 1, NUM = 2 };

typedef struct CalcData {
  int type;
  char op;
  long long num;
} CalcData;

typedef struct CalcStack {
  int top;
  CalcData data[100000];
} CalcStack;

void push(CalcStack* stack, CalcData val);
CalcData pop(CalcStack* stack);
int size(CalcStack* stack);