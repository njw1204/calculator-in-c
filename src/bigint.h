#pragma once
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR 1
#define BIGINT_MAX_LEN 9999
#define BIGINT_SIZE BIGINT_MAX_LEN+2

typedef struct {
  int len;
  char sign;
  char num[BIGINT_SIZE];
} BigInt;

void Get(const BigInt* var, char* num);
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