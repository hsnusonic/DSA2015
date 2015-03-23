#include <iostream>
#include <string> // stoi()
#include "biginteger_for_binary.h"
#include <iomanip> // setw() & setfill()

using namespace std;

BigInteger::BigInteger(const int& a) {
  IntegerArray[0] = a;
  ArrayLength = 1;
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
    while (IntegerArray[digit] == big.IntegerArray[digit])
      digit--;
    return IntegerArray[digit] < big.IntegerArray[digit];
  }
  else if (ArrayLength > big.ArrayLength)
    return false;
  else
    return true;
}

const BigInteger BigInteger::operator-(const BigInteger& big) const{
  // suppose "big" is smaller
  BigInteger out;
  int compensate = 0;
  for (int i = 0; i < big.ArrayLength; i++){
    if (IntegerArray[i]-compensate < big.IntegerArray[i]){
      out.IntegerArray[i] = Base + IntegerArray[i] - compensate - big.IntegerArray[i];
      compensate = 1;
      out.ArrayLength ++;
    } else {
      out.IntegerArray[i] = IntegerArray[i] - compensate - big.IntegerArray[i];
      compensate = 0;
      out.ArrayLength += out.IntegerArray[i]? 1:0;
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

BigInteger& BigInteger::operator/=(int a) {
  int i = ArrayLength - 1;
  int divide = IntegerArray[i] / a;
  int mod = IntegerArray[i] % a;
  if (!divide)
    ArrayLength --;
  else if (i > 0){
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

BigInteger& BigInteger::operator=(const BigInteger& big){
  for (int i = ArrayLength-1; i >= 0; i--){
    if (i >= big.ArrayLength)
     IntegerArray[i] = 0;
    else
     IntegerArray[i] = big.IntegerArray[i];
  }
  ArrayLength = big.ArrayLength;
  return *this;
}

bool BigInteger::iseven(){
  return (IntegerArray[0] % 2)? false:true;
}

bool BigInteger::iszero(){
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
