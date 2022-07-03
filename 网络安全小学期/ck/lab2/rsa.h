/*
 * RSA 实现类
 */

#ifndef RSA
#define RSA
#include "bigint.h"
using namespace bigint;
// 类型名不能全大写
class Rsa {
private:
  Bigint n;
  Bigint public_key;
  Bigint private_key;
  int key_len;

public:
  void get_key();
  void encryption(std::string filename, std::string out);
  void encryption();
  void decrypt(std::string filename, std::string out);
  void decrypt();
};
#endif
