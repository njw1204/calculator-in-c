#pragma once
#include "bigint.h"
#define MAX_STACK 50100

enum TYPE { OP = 1, NUM = 2 };

typedef struct CalcData {
  int type;
  char op;
  BigInt num;
} CalcData;

typedef struct CalcStack {
  int top;
  CalcData data[MAX_STACK];
} CalcStack;

void push(CalcStack* stack, const CalcData* val);
CalcData* pop(CalcStack* stack);
CalcData* top(CalcStack* stack);
int size(const CalcStack* stack);
void clear(CalcStack* stack);