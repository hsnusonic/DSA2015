#include <iostream>
#include <stdio.h>

int gcd_by_binary(const int& a, int& b){
  int n, m;
  int ans = 1;

  if (a < b){
    n = a; m = b;
  } else {
    n = b; m = a;
  }

  while(n != 0 && m != 0){
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

int gcd_by_euclid(const int& a, int& b){
  int n, m;

  if (a < b){
    n = a; m = b;
  }
  else{
    n = b; m = a;
  }

  while (m % n != 0){
    int tmp;
    tmp = n;
    n = m % n;
    m = tmp;
  }

  return n;
}

int main(void){
  int a, b;
  scanf("%d %d", &a, &b);
  while (a > 0 && b > 0) {
    printf("gcd_by_binary is %d\n", gcd_by_binary(a, b));
    printf("gcd_by_euclid is %d\n", gcd_by_euclid(a, b));
    scanf("%d %d", &a, &b);
  }
  return 0;
}
