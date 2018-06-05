#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "bigint.h"
#include "flag.h"

static void EraseLeadZero(BigInt* var);
static void GetMulOneDigitData(const BigInt* var, BigInt* mulOneResult, int* errorFlagResult);

void Get(const BigInt* var, char* num) {
  int pos = 0;
  memset(num, 0, BIGINT_SIZE);
  if (var->sign == -1 && !IsZero(var)) num[pos++] = '-';
  for (int i = var->len - 1; i >= 0; i--, pos++)
    num[pos] = var->num[i];
}


void GetRaw(const BigInt* var, char* sign, int* len, char* bigIntRawStr) {
  if (sign) *sign = var->sign;
  if (len) *len = var->len;
  if (bigIntRawStr) memcpy(bigIntRawStr, var->num, BIGINT_SIZE);
}


int Set(BigInt* var, const char* num) {
  Reset(var);
  for (int i = strlen(num) - 1, p = 0; i >= 0; i--, p++) {
    if (num[i] >= '0' && num[i] <= '9') {
      if (p >= BIGINT_MAX_LEN) {
        Reset(var);
        return ERROR;
      }
      else var->num[p] = num[i];
    }
    else if (i != 0 || (num[i] != '+' && num[i] != '-')) {
      Reset(var);
      return ERROR;
    }
    else if (num[i] == '-')
      var->sign = -1;
  }

  var->len = strlen(var->num);
  EraseLeadZero(var);

  if (IsZero(var)) var->sign = 1;
  return SUCCESS;
}


int SetRaw(BigInt* var, char sign, int len, const char* bigIntRawStr) {
  if (len > BIGINT_MAX_LEN) {
    Reset(var);
    return ERROR;
  }
  var->sign = sign;
  var->len = len;
  memset(var->num, 0, BIGINT_SIZE);
  memcpy(var->num, bigIntRawStr, len);
  if (IsZero(var)) var->sign = 1;
  return SUCCESS;
}


void Copy(BigInt* dest, const BigInt* source) {
  dest->len = source->len;
  dest->sign = source->sign;
  memcpy(dest->num, source->num, BIGINT_SIZE);
}


void Swap(BigInt* left, BigInt* right) {
  int maxLen, minLen, maxSide;
  if (left->len > right->len) {
    maxLen = left->len;
    minLen = right->len;
    maxSide = -1;
  }
  else {
    maxLen = right->len;
    minLen = left->len;
    maxSide = 1;
  }
  
  for (int i = 0; i < maxLen; i++) {
    if (i < minLen) {
      char t = left->num[i];
      left->num[i] = right->num[i];
      right->num[i] = t;
    }
    else if (maxSide == -1) {
      right->num[i] = left->num[i];
      left->num[i] = 0;
    }
    else {
      left->num[i] = right->num[i];
      right->num[i] = 0;
    }
  }

  int ti = left->len;
  left->len = right->len;
  right->len = ti;

  char tc = left->sign;
  left->sign = right->sign;
  right->sign = tc;
}


void Reset(BigInt* var) {
  var->sign = 1;
  var->len = 0;
  memset(var->num, 0, BIGINT_SIZE);
}


int Compare(const BigInt* left, const BigInt* right, int absolute) {
  if (absolute == FALSE) {
    if (left->sign == 1 && right->sign == 1)
      return Compare(left, right, TRUE);
    else if (left->sign == -1 && right->sign == -1)
      return Compare(right, left, TRUE);
    else
      return left->sign;
  }

  if (left->len < right->len) return -1;
  else if (left->len > right->len) return 1;

  for (int i = left->len - 1; i >= 0; i--) {
    if (left->num[i] < right->num[i]) return -1;
    else if (left->num[i] > right->num[i]) return 1;
  }

  return 0;
}


int IsZero(const BigInt* val) {
  if (val->len == 1 && val->num[0] == '0') return 1;
  else return 0;
}


int Add(BigInt* left, BigInt* right) {
  if (Compare(left, right, TRUE) == -1)
    Swap(left, right);

  if (IsZero(right)) {
    Reset(right);
    return SUCCESS;
  }

  if (left->sign == right->sign) {
    int carry = 0;
    for (int i = 0; i < left->len; i++) {
      int sum = left->num[i] - '0' + carry;
      if (i < right->len) sum += right->num[i] - '0';
      if (sum >= 10) {
        sum -= 10;
        carry = 1;
      }
      else carry = 0;
      left->num[i] = sum + '0';
    }

    if (carry) {
      if (left->len >= BIGINT_MAX_LEN) {
        Reset(left);
        Reset(right);
        return ERROR;
      }
      else {
        left->num[left->len] = '1';
        left->num[left->len + 1] = 0;
        left->len++;
      }
    }

    if (IsZero(left)) left->sign = 1;
    Reset(right);
    return SUCCESS;
  }
  else {
    BigInt t;
    Copy(&t, right);
    t.sign = left->sign;
    return Sub(left, &t);
  }
}


int Sub(BigInt* left, BigInt* right) {
  if (left->sign != right->sign) {
    BigInt t;
    Copy(&t, right);
    t.sign = left->sign;
    return Add(left, &t);
  }
  else if (left->sign == -1 && right->sign == -1) {
    Swap(left, right);
    left->sign = 1;
    right->sign = 1;
    return Sub(left, right);
  }

  int signFlag, cmp = Compare(left, right, TRUE);
  if (cmp == -1) {
    Swap(left, right);
    signFlag = -1;
  }
  else if (cmp == 1) {
    signFlag = 1;
  }
  else {
    memset(left->num, 0, BIGINT_SIZE);
    left->num[0] = '0';
    left->len = 1;
    left->sign = 1;
    Reset(right);
    return SUCCESS;
  }

  if (IsZero(right)) {
    Reset(right);
    return SUCCESS;
  }

  int carry = 0;
  for (int i = 0; i < left->len; i++) {
    int sum = left->num[i] - '0' + carry;
    if (i < right->len) sum -= right->num[i] - '0';
    if (sum < 0) {
      sum += 10;
      carry = -1;
    }
    else carry = 0;
    left->num[i] = sum + '0';
  }

  left->sign = signFlag;
  EraseLeadZero(left);
  if (IsZero(left)) left->sign = 1;
  Reset(right);
  return SUCCESS;
}


int Mul10(BigInt* val, int count) {
  if (IsZero(val)) return SUCCESS;
  if (val->len + count > BIGINT_MAX_LEN) {
    Reset(val);
    return ERROR;
  }
  memmove(val->num + count, val->num, val->len);
  for (int i = 0; i < count; i++) val->num[i] = '0';
  val->len += count;
  val->num[val->len] = 0;
  return SUCCESS;
}


int Mul(BigInt* left, BigInt* right) {
  int signFlag;
  if (left->sign == right->sign) signFlag = 1;
  else signFlag = -1;
  left->sign = 1;
  right->sign = 1;

  if (IsZero(left) || IsZero(right)) {
    SetRaw(left, 1, 1, "0");
    Reset(right);
    return SUCCESS;
  }

  BigInt mulOne[10], temp;
  int errorFlag[10] = {SUCCESS};
  GetMulOneDigitData(left, mulOne, errorFlag);
  SetRaw(left, 1, 1, "0");

  for (int i = 0; i < right->len; i++) {
    if (right->num[i] == '0') continue;
    if (errorFlag[right->num[i] - '0'] == ERROR) {
      Reset(left);
      Reset(right);
      return ERROR;
    }
    Copy(&temp, &mulOne[right->num[i] - '0']);
    if (Mul10(&temp, i) == ERROR) {
      Reset(left);
      Reset(right);
      return ERROR;
    }
    if (Add(left, &temp) == ERROR) {
      Reset(left);
      Reset(right);
      return ERROR;
    }
  }

  left->sign = signFlag;
  if (IsZero(left)) left->sign = 1;
  Reset(right);
  return SUCCESS;
}


static void EraseLeadZero(BigInt* var) {
  for (int i = var->len - 1; i >= 1; i--) {
    if (var->num[i] == '0') {
      var->num[i] = 0;
      var->len--;
    }
    else break;
  }
}


static void GetMulOneDigitData(const BigInt* var, BigInt* mulOneResult, int* errorFlagResult) {
  BigInt temp;
  SetRaw(mulOneResult, 1, 1, "0");
  for (int i = 1; i <= 9; i++) {
    if (errorFlagResult[i - 1] == ERROR) {
      errorFlagResult[i] = ERROR;
      continue;
    }
    Copy(mulOneResult + i, mulOneResult + i - 1);
    Copy(&temp, var);
    if (Add(mulOneResult + i, &temp) == ERROR) errorFlagResult[i] = ERROR;
  }
}


void BigIntTest() {
  BigInt a, b;
  char num[BIGINT_SIZE], num2[BIGINT_SIZE], num3[BIGINT_SIZE];

  printf("A = ");
  scanf("%s", num);
  printf("B = ");
  scanf("%s", num2);

  Set(&a, num);
  Set(&b, num2);
  Add(&a, &b);
  Get(&a, num3);
  printf("A + B = %s\n", num3);

  Set(&a, num);
  Set(&b, num2);
  Sub(&a, &b);
  Get(&a, num3);
  printf("A - B = %s\n", num3);

  Set(&a, num);
  Set(&b, num2);
  Mul(&a, &b);
  Get(&a, num3);
  printf("A x B = %s\n", num3);
}