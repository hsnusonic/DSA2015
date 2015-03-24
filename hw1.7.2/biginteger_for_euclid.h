#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

#define Base 10000

class BigInteger{
public:
  BigInteger(){};
  BigInteger(const int&);
  BigInteger(const std::string&);
  BigInteger(const BigInteger&);
  ~BigInteger(){};

  bool operator<(const BigInteger&) const;
  bool operator==(const BigInteger&) const;
  bool operator<=(const BigInteger&) const;
  const BigInteger operator%(const BigInteger&) const;
  BigInteger& operator=(const BigInteger&);
  bool iszero() const;

  BigInteger& operator*=(int);
  BigInteger& operator/=(int);
  const BigInteger operator+(const BigInteger&) const;
  const BigInteger operator-(const BigInteger&) const;
  const BigInteger operator*(const BigInteger&) const;
  const BigInteger degrade(int) const;
/*  const BigInteger upgrade(int) const;*/

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

private:
  int IntegerArray[128] = {0};
  int ArrayLength = 1;
};


#endif
