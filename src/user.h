#pragma once
#include <stdio.h>
#include <string.h>
#include "calc.h"
#include "stack.h"
#include "parse.h"

void Intro();
int InputExp(char* dest);
void PrintResult(long long result);