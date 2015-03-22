#include <iostream>

using namespace std;

int gcd_by_reverse_search(const int& a, const int& b, int& count){
  for (int i = a < b ? a : b; i >= 1; i--){
    count ++;
    if (a % i == 0 && b % i == 0)
      return i;
  }
  return 0;
}

int gcd_by_filter(const int& a, const int& b, int& count){
  int min = a < b ? a : b;
  for (int i = 2; i <= min; i++){
    count ++;
    if (a % i == 0 && b % i == 0)
      return i * gcd_by_filter(a/i, b/i, count);
  }
  return 1;
}

int gcd_by_filter_faster_internal(const int& a, const int& b, int s, int& count){
  int min = a < b ? a : b;
  for (int i = s; i <= min; i++){
    count ++;
    if (a % i == 0 && b % i == 0)
      return i * gcd_by_filter_faster_internal(a/i, b/i, i, count);
  }
  return 1;
}

int gcd_by_filter_faster(const int& a, const int& b, int& count){
  return gcd_by_filter_faster_internal(a, b, 2, count);
}

int gcd_by_binary(const int& a, const int& b, int& count){
  int n, m;
  int ans = 1;

  if (a < b){
    n = a; m = b;
  } else {
    n = b; m = a;
  }

  while(n != 0 && m != 0){
    count ++;
    if (n % 2 == 0){
      if (m % 2 == 0){
        ans *= 2;
        n /= 2;
        m /= 2;
      }
      else
        n /= 2;
    }
    else if (m % 2 == 0)
      m /= 2;
    if (m < n){
      int tmp;
      tmp = n; n = m; m = tmp;
    }
    m = m - n;
  }

  return (n * ans);
}

int gcd_by_euclid(const int& a, const int& b, int& count){
  int n, m;

  if (a < b){
    n = a; m = b;
  }
  else{
    n = b; m = a;
  }

  while (m % n != 0){
    count ++;
    int tmp;
    tmp = n;
    n = m % n;
    m = tmp;
  }

  return n;
}

int main(void){
  int a, b;
  int ans, count;
  cin >> a;
  while (a > 0) {
    cin >> b;
    count = 0;
    ans = gcd_by_reverse_search(a, b, count);
    cout << "Case (" << a << ", " << b << "): GCD-By-Reverse-Search = " << ans <<\
      ", taking " << count << " iterations" << endl;
    count = 0;
    ans = gcd_by_filter(a, b, count);
    cout << "Case (" << a << ", " << b << "): GCD-By-Filter = " << ans <<\
      ", taking " << count << " iterations" << endl;
    count = 0;
    ans = gcd_by_filter_faster(a, b, count);
    cout << "Case (" << a << ", " << b << "): GCD-By-Filter-Faster = " << ans <<\
      ", taking " << count << " iterations" << endl;
    count = 0;
    ans = gcd_by_binary(a, b, count);
    cout << "Case (" << a << ", " << b << "): GCD-By-Binary = " << ans <<\
      ", taking " << count << " iterations" << endl;
    count = 0;
    ans = gcd_by_euclid(a, b, count);
    cout << "Case (" << a << ", " << b << "): GCD-By-Euclid = " << ans <<\
      ", taking " << count << " iterations" << endl;
    cin >> a;
  }
  return 0;
}
