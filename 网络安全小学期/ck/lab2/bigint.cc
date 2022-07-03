#include "bigint.h"
#include <gmp.h>
#include <memory>

namespace bigint {

Bigint get_rand_num(int bits) {
  Bigint_rand randz(gmp_randinit_default);
  randz.seed(rand());
  Bigint bit = bits;
  return randz.get_z_bits(bit);
}

Bigint get_rand_prime(int bits) {
  Bigint prime;
  std::unique_ptr<Bigint> tmp = std::make_unique<Bigint>();
  // Bigint *tmp = new Bigint[1];
  prime = get_rand_num(bits);
  mpz_nextprime(tmp->get_mpz_t(), prime.get_mpz_t());
  prime = *tmp;
  // delete[] tmp;
  return prime;
}

// 大数模乘
Bigint mul(Bigint a, Bigint b, Bigint mod) {
  Bigint ans = 0;
  while (b > 0) {
    if (b % 2 == 1)
      ans = (ans + a) % mod; // 奇数处理
    a = (a + a) % mod;
    b /= 2;
  }
  return ans;
}
// 大数模幂
Bigint pow(Bigint base, Bigint power, Bigint mod) {
  Bigint ans = 1;
  while (power > 0) {
    if (power % 2 == 1)
      ans = mul(ans, base, mod); // 奇数处理
    base = mul(base, base, mod);
    power /= 2;
  }
  return ans % mod;
}

// 辗转相除法
Bigint gcd(Bigint &a, Bigint &b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

Bigint exgcd(Bigint a, Bigint b, Bigint &x, Bigint &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  Bigint d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

Bigint reverse_rsa(Bigint &a, Bigint &b) {
  Bigint d, x, y;
  d = exgcd(a, b, x, y);
  if (d == 1)
    return (x % b + b) % b;
  else
    return -1;
}

bool isprime(Bigint &num) {
  if (num == 2)
    return true; // 2为质数保留
  if (num % 2 != 1 || num < 2)
    return false; // 筛掉偶数和小于2的数
  Bigint s = 0, t = num - 1;
  while (t % 2 != 1) { // 当t为偶数时，继续分解, s递增
    s++;
    t /= 2;
  }
  for (int i = 0; i < 10;
       i++) { // 二次探测定理, 进行十次探测, 使方程a^(num-1)=1(mod
              // num)成立的解有仅有a=1或者a=num-1
    Bigint_rand randz(gmp_randinit_default);
    Bigint a = randz.get_z_range(num - 1); // 随机整数a，取(1, num-1)
    Bigint x = pow(a, t, num);             // x为二次探测的解
    for (int j = 0; j < s; j++) {          // x^s=a^(num-1)
      Bigint test = mul(x, x, num);
      if (test == 1 && x != 1 && x != num - 1)
        return false; // 若平方取模结果为1，但x不是1或者num-1，则num不是质数
      x = test;
    }
    if (x != 1)
      return false; // 费马小定理
  }
  return true;
}
} // namespace bigint
