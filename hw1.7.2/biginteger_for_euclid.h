#ifndef BIGINTEGER_FOR_EUCLID

#define BIGINTEGER_FOR_EUCLID

#define Base 10

class BigInteger{
public:
  BigInteger(){};
  BigInteger(const int&);
  BigInteger(const std::string&);
  BigInteger(const BigInteger&);
  ~BigInteger(){};

  bool operator<(const BigInteger&) const;
  bool operator==(const BigInteger&) const;
  const BigInteger operator%(const BigInteger&) const;
  BigInteger& operator=(const BigInteger&);
  bool iszero() const;

  BigInteger& operator*=(int);
  const BigInteger operator-(const BigInteger&) const;
  const BigInteger operator*(const BigInteger&) const;
  int getdigit() const;
  void calculate();
  void refreshdigit();

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

private:
  int IntegerArray[512] = {0};
  int digit = 0;
};


#endif
