#ifndef BIGINT
#define BIGINT
#include <gmp.h>
#include <gmpxx.h>

namespace bigint {
// 重命名大数
typedef mpz_class Bigint;
// 重命名随机数
typedef gmp_randclass Bigint_rand;
// 随机生成大数
Bigint get_rand_num(int bits);
// 得到随机素数
Bigint get_rand_prime(int bits);
// Miller Rabin 素数判定
bool isprime(Bigint &num);
// 大数模乘 Montgomery
Bigint mul(Bigint a, Bigint b, Bigint mod);
// 大数模幂 Montgomery
Bigint pow(Bigint base, Bigint power, Bigint mod);
// 扩展欧几里德算法 求最大公约数
Bigint exgcd(Bigint a, Bigint b, Bigint &x, Bigint &y);
// 求逆元
Bigint reverse_rsa(Bigint &a, Bigint &b);
// 互素判断
Bigint gcd(Bigint &a, Bigint &b);
//
} // namespace bigint
#endif
