#include <iostream>
#include <string> // stoi()
#include "biginteger_for_euclid.h"
#include <iomanip> // setw() & setfill()
#include <math.h> // log10

using namespace std;

BigInteger::BigInteger(const int& a) {
  int mod = a / Base;
  IntegerArray[0] = a % Base;
  ArrayLength = 1;
  while (mod > 0){
    IntegerArray[ArrayLength] = mod;
    ArrayLength ++;
    mod = mod / Base;
  }
}

BigInteger::BigInteger(const string& str) {
  ArrayLength = (str.size() % 4)? str.size()/4+1 : str.size()/4;
  int length = str.size();
  for (int i = 0; i < ArrayLength; i++){
    if (length > 4)
      IntegerArray[i] = stoi( str.substr( length -= 4, 4) );
    else
      IntegerArray[i] = stoi( str.substr(0, length) );
  }
}

BigInteger::BigInteger(const BigInteger& big) {
  ArrayLength = big.ArrayLength;
  for (int i = 0; i < ArrayLength; i++)
    IntegerArray[i] = big.IntegerArray[i];
}

bool BigInteger::operator<(const BigInteger& big) const {
  if (ArrayLength == big.ArrayLength){
    int digit = ArrayLength - 1;
    while (IntegerArray[digit] == big.IntegerArray[digit] && digit > 0)
      digit--;
    return IntegerArray[digit] < big.IntegerArray[digit];
  }
  else if (ArrayLength > big.ArrayLength)
    return false;
  else
    return true;
}

bool BigInteger::operator==(const BigInteger& big) const {
  if (ArrayLength != big.ArrayLength)
    return false;
  else{
    for (int i = 0; i < ArrayLength; i++){
      if (IntegerArray[i] != big.IntegerArray[i])
        return false;
    }
  }
  return true;
}

bool BigInteger::operator<=(const BigInteger& big) const {
  if ((*this) < big || (*this) == big)
    return true;
  else
    return false;
}

const BigInteger BigInteger::operator+(const BigInteger& big) const{
  BigInteger out;
  int upper = big.ArrayLength;
  if ((*this) < big)
    upper = big.ArrayLength;
  else
    upper = ArrayLength;

  for (int i = 0; i < upper; i++){
    int plus = IntegerArray[i] + big.IntegerArray[i];
    if (plus >= Base){
      out.IntegerArray[i+1] = 1;
      out.IntegerArray[i] = plus - Base;
      out.ArrayLength = i + 2;
    } else {
      out.IntegerArray[i] = plus;
      out.ArrayLength = i + 1;
    }
  }
  return out;
}

const BigInteger BigInteger::operator-(const BigInteger& big) const{
  // suppose "big" is smaller
  BigInteger out;
  int compensate = 0;
  for (int i = 0; i < big.ArrayLength; i++){
    int newdigit = IntegerArray[i] - compensate;
    if (newdigit < big.IntegerArray[i]){
      out.IntegerArray[i] = Base + newdigit - big.IntegerArray[i];
      compensate = 1;
      out.ArrayLength = i+1;
    } else {
      out.IntegerArray[i] = IntegerArray[i] - compensate - big.IntegerArray[i];
      compensate = 0;
      if (out.IntegerArray[i])
        out.ArrayLength = i+1;
    }
  }
  for (int i = big.ArrayLength; i < ArrayLength; i++){
    int newdigit = IntegerArray[i] - compensate;
    if (newdigit < 0){
      out.IntegerArray[i] = Base + newdigit;
      compensate = 1;
      out.ArrayLength = i+1;
    } else if (newdigit > 0){
      out.IntegerArray[i] = newdigit;
      out.ArrayLength = i+1;
      compensate = 0;
    }
  }
  return out;
}

const BigInteger BigInteger::operator*(const BigInteger& big) const{
  BigInteger out;
  int product;
  for (int i = 0; i < ArrayLength; i++){
    for (int j = 0; j < big.ArrayLength; j++){
      product = IntegerArray[i] * big.IntegerArray[j];
      if (product >= Base){
        out.IntegerArray[i+j] += (product % Base);
        out.IntegerArray[i+j+1] += (product / Base);
        if ((i+j+2) > out.ArrayLength)
          out.ArrayLength = i+j+2;
      } else {
        out.IntegerArray[i+j] += product;
        if ((i+j+1) > out.ArrayLength)
          out.ArrayLength = i+j+1;
      }
    }
  }
  return out;
}

const BigInteger BigInteger::degrade(int digit) const{
  BigInteger out;
  if (ArrayLength > digit){
    out.ArrayLength = ArrayLength - digit;
    for (int i = 0; i < out.ArrayLength; i++){
      out.IntegerArray[i] = IntegerArray[i+digit];
    }
  }
  return out;
}
/*
const BigInteger BigInteger::upgrade(int digit) const{
  // input digit to mutiply
  BigInteger out;
  out.IntegerArray[digit] = IntegerArray[0];
  if (digit >0)
    out.ArrayLength = digit + 1;
  return out;
}
*/
BigInteger& BigInteger::operator/=(int a) {
  int i = ArrayLength - 1;
  int divide = IntegerArray[i] / a;
  int mod = IntegerArray[i] % a;
  if (!divide && i > 0) {
    ArrayLength --;
    IntegerArray[i] = divide;
    IntegerArray[i-1] += Base * mod;
  } else if (i>0){
    IntegerArray[i] = divide;
    IntegerArray[i-1] += Base * mod;
  } else {
    IntegerArray[i] = divide;
  }

  for (i -= 1; i >= 0; i--){
    divide = IntegerArray[i] / a;
    mod = IntegerArray[i] % a;
    if (divide && i > 0){
      IntegerArray[i] = divide;
      IntegerArray[i-1] += Base * mod;
    } else if (divide && i==0){
      IntegerArray[i] = divide;
    }
  }
  return *this;
}

BigInteger& BigInteger::operator*=(int a) {
  int product;
  for (int i = 0; i < ArrayLength; i++){
    product = IntegerArray[i] * a;
    if (product >= Base){
      IntegerArray[i] = product % Base;
      IntegerArray[i+1] += (product / Base);
      if ( (i+1) > ArrayLength)
        ArrayLength = i + 1;
    } else {
      IntegerArray[i] = product;
    }
  }
  return *this;
}

const BigInteger BigInteger::operator%(const BigInteger& big) const{
  // suppose "big" is smaller

  int upperbound = ArrayLength - big.ArrayLength;
  BigInteger tmp = big.upgrade(upperbound);
  while (tmp < (*this))
    tmp *= 2;
  cout << tmp << endl;
  while ((*this) < tmp) {
    tmp = tmp - big;
    cout << tmp << endl;
  }

  return (*this) - tmp;
}

BigInteger& BigInteger::operator=(const BigInteger& big){
  if ( (*this) < big){
    for (int i = 0; i < big.ArrayLength; i++){
      IntegerArray[i] = big.IntegerArray[i];
    }
  } else {
    for (int i = 0; i < ArrayLength; i++){
      IntegerArray[i] = big.IntegerArray[i];
    }
  }
  ArrayLength = big.ArrayLength;
  return (*this);
}

bool BigInteger::iszero() const{
  if (ArrayLength == 1 && IntegerArray[0] == 0)
    return true;
  else
    return false;
}

ostream& operator<<(ostream& out, const BigInteger& a) {
  out << a.IntegerArray[a.ArrayLength-1];
  for (int i = a.ArrayLength-2; i >= 0; i--)
      out << setw(4) << setfill('0') << a.IntegerArray[i];
  return out;
}
