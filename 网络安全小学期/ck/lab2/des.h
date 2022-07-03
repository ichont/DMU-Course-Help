#ifndef DES
#define DES
#include <bitset>
#include <string>
class Des {
private:
  std::bitset<64> key;        // 64位密钥
  std::bitset<48> subKey[16]; // 存放16轮子密钥
public:
  std::bitset<64> charToBitset(const char s[8]);
  std::bitset<32> f(std::bitset<32> R, std::bitset<48> k);
  std::bitset<28> leftShift(std::bitset<28> k, int shift);
  void get_key();
  void encrypt(std::string filename, std::string outfile);
  void decrypt(std::string filename, std::string outfile);
  std::bitset<64> encrypt(std::bitset<64> &plain);
  std::bitset<64> decrypt(std::bitset<64> &cipher);
};
#endif
