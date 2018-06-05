#pragma once
#define BIGINT_MAX_LEN 9999
#define BIGINT_SIZE BIGINT_MAX_LEN+2

typedef struct {
  char sign;
  int len;
  char num[BIGINT_SIZE];
} BigInt;

void Get(const BigInt* var, char* num);
void GetRaw(const BigInt* var, char* sign, int* len, char* bigIntRawStr);
int Set(BigInt* var, const char* num);
int SetRaw(BigInt* var, char sign, int len, const char* bigIntRawStr);
void Copy(BigInt* dest, const BigInt* source);
void Swap(BigInt* left, BigInt* right);
void Reset(BigInt* var);
int Compare(const BigInt* left, const BigInt* right, int absolute);
int IsZero(const BigInt* val);
int Add(BigInt* left, BigInt* right);
int Sub(BigInt* left, BigInt* right);
int Mul10(BigInt* val, int count);
int Mul(BigInt* left, BigInt* right);