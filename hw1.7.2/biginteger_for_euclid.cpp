#include <iostream>
#include <string> // stoi()
#include "biginteger_for_euclid.h"
#include <iomanip> // setw() & setfill()
#include <math.h> // log10

using namespace std;

BigInteger::BigInteger(const int& a) {
  int Q = a;
  for (int i = 0; Q != 0; i++) {
    IntegerArray[i] = Q % Base;
    Q /= Base;
  }
  (*this).refreshdigit();
}

BigInteger::BigInteger(const string& str) {
  int len = str.size();
  for (int i = 0; i < len; ++i) {
    IntegerArray[i] = str[len-i-1] - '0';
  }
  (*this).refreshdigit();
}

BigInteger::BigInteger(const BigInteger& big) {
  digit = big.digit;
  for (int i = 0; i <= digit; i++)
    IntegerArray[i] = big.IntegerArray[i];
}

bool BigInteger::operator<(const BigInteger& big) const {
  if (digit == big.digit) {
    for (int i = digit-1; i >= 0; i--) {
      if (IntegerArray[i] != big.IntegerArray[i])
        return IntegerArray[i] < big.IntegerArray[i];
    }
    return false;
  }
  else if (digit > big.digit)
    return false;
  else
    return true;
}

void BigInteger::refreshdigit() {
  digit = 0;
  for (int i = 511; i >= 0; i--) {
    if (IntegerArray[i]) {
      digit = i + 1;
      break;
    }
  }
}

bool BigInteger::operator==(const BigInteger& big) const {
  if (digit == big.digit) {
    for (int i = 0; i < digit; i++) {
      if (IntegerArray[i] != big.IntegerArray[i])
        return false;
    }
    return true;
  }
  return false;
}

const BigInteger BigInteger::operator-(const BigInteger& big) const{
  // suppose "big" is smaller
  BigInteger out;
  int compensate = 0;
  for (int i = 0; i < big.digit; i++){
    int newdigit = IntegerArray[i] - compensate;
    if (newdigit < big.IntegerArray[i]){
      out.IntegerArray[i] = Base + newdigit - big.IntegerArray[i];
      compensate = 1;
    } else {
      out.IntegerArray[i] = newdigit - big.IntegerArray[i];
      compensate = 0;
    }
  }
  for (int i = big.digit; i < digit; i++){
    int newdigit = IntegerArray[i] - compensate;
    if (newdigit < 0){
      out.IntegerArray[i] = Base + newdigit;
      compensate = 1;
    } else {
      out.IntegerArray[i] = newdigit;
      compensate = 0;
    }
  }
  out.refreshdigit();
  return out;
}

const BigInteger BigInteger::operator*(const BigInteger& big) const{
  BigInteger out;
  int product;
  for (int i = 0; i < digit; i++){
    for (int j = 0; j < big.digit; j++){
      product = IntegerArray[i] * big.IntegerArray[j];
      out.IntegerArray[i+j] += (product % Base);
      out.IntegerArray[i+j+1] += (product / Base);
    }
  }
  out.refreshdigit();
  out.calculate();
  return out;
}

BigInteger& BigInteger::operator*=(int a) {
  BigInteger tmp(a);
  (*this) = (*this) * tmp;
  (*this).refreshdigit();
  return *this;
}

const BigInteger BigInteger::operator%(const BigInteger& big) const{
  // suppose "big" is smaller
  BigInteger tmp;
  int diff = digit - big.digit;

  for (int k = 0; k < (big.digit-1); k++) {
    tmp.IntegerArray[k] += IntegerArray[diff + k +1];
    tmp.refreshdigit();
  }

  for (int i = digit - big.digit; i >= 0; i--){
    tmp *= Base;
    tmp.IntegerArray[0] = IntegerArray[i];
    tmp.refreshdigit();

    while (big < tmp || big == tmp) {
      tmp = tmp - big;
    }
  }

  return tmp;
}

BigInteger& BigInteger::operator=(const BigInteger& big){
  for (int i = 0; i < big.digit; i++) {
    IntegerArray[i] = big.IntegerArray[i];
  }
  if (digit > big.digit) {
    for (int i = big.digit; i < digit; i++)
     IntegerArray[i] = 0;
  }
  (*this).refreshdigit();
  return (*this);
}

bool BigInteger::iszero() const{
  return digit? false:true;
}

int BigInteger::getdigit() const{
  return digit;
}

void BigInteger::calculate() {
  for (int i = 0; i < digit; i++) {
    if (IntegerArray[i] >= Base) {
      IntegerArray[i+1] += IntegerArray[i] / Base;
      IntegerArray[i] = IntegerArray[i] % Base;
    }
  }
  (*this).refreshdigit();
}

ostream& operator<<(ostream& out, const BigInteger& a) {
  for (int i = a.digit -1; i >= 0; i--)
      out << setw(1) << setfill('0') << a.IntegerArray[i];
  return out;
}
