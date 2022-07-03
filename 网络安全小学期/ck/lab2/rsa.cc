#include "rsa.h"
#include "bigint.h"
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

void Rsa::get_key() {
  // 素数长度为key的一半
  std::cout << "请输入密钥长度: ";
  std::cin >> key_len;
  int prime_len = key_len / 2;
  // 得到P,Q
  Bigint P = get_rand_prime(prime_len);
  Bigint Q = get_rand_prime(prime_len);
  // 计算 N 和 欧拉函数 O
  std::cout << "随机生成质数P: " << P << std::endl;
  std::cout << "随机生成质数Q: " << Q << std::endl;
  Bigint N = P * Q;
  n = N;
  Bigint O = (P - 1) * (Q - 1);
  std::cout << "得到 N ：" << N << std::endl;
  std::cout << "得到 R ：" << O << std::endl;
  // 并行计算 计算公钥
  bool sign(true);
  std::mutex mu;
  // 使用8个线程并行
  std::vector<std::thread> threads;
  std::cout << "计算公钥" << std::endl;
  unsigned concurrent_count = std::thread::hardware_concurrency(); //
  std::cout << "计算线程数: " << concurrent_count << std::endl;
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < concurrent_count; i++) {
    threads.push_back(std::thread([&sign, O, this, &mu]() {
      while (sign) {
        Bigint E = get_rand_num(key_len);
        if (1 < E && E < O && isprime(E) && gcd(E, O) == 1) {
          mu.lock();
          sign = false;
          public_key = E;
          mu.unlock();
        }
      }
    }));
  }
  for (auto &i : threads) {
    i.join();
  }
  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "花费了"
            << double(duration.count()) *
                   std::chrono::microseconds::period::num /
                   std::chrono::microseconds::period::den
            << "秒" << std::endl;
  /*
  Bigint E;
  auto start = std::chrono::system_clock::now();
  while (sign) {
    E = get_rand_num(key_len);
    if (1 < E && E < O && isprime(E) && gcd(E, O) == 1)
      break;
  }
  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "花费了"
            << double(duration.count()) *
                   std::chrono::microseconds::period::num /
                   std::chrono::microseconds::period::den
            << "秒" << std::endl;

  public_key = E;

    */
  // 计算私钥
  private_key = reverse_rsa(public_key, O);
  // 打印出来
  std::cout << "得到公钥: (" << N.get_str() << "," << public_key.get_str()
            << ")" << std::endl;
  std::cout << "得到私钥: (" << N.get_str() << "," << private_key.get_str()
            << ")" << std::endl;
}
void String_Split(const std::string &str, const char split,
                  std::vector<std::string> &res) {
  if (str == "")
    return;
  // 在字符串末尾也加入分隔符，方便截取最后一段
  std::string strextend = str; // +split;
  size_t pos = strextend.find(split);
  // 若找不到内容则字符串搜索函数返回 npos
  while (pos != strextend.npos) {
    std::string temp = strextend.substr(0, pos);
    res.push_back(temp);
    // 去掉已分割的字符串,在剩下的字符串中进行分割
    strextend = strextend.substr(pos + 1, strextend.size());
    pos = strextend.find(split);
  }
}
void Rsa::encryption(std::string filename, std::string out) {
  get_key();
  // 读取文件到string
  std::ifstream f(filename);
  std::stringstream s;
  s << f.rdbuf();
  f.close();
  //加密
  std::cout << "开始加密" << std::endl;
  std::string ans;
  auto start = std::chrono::system_clock::now();
  for (auto i : s.str()) {
    Bigint b = static_cast<unsigned char>(i);
    Bigint a = pow(b, public_key, n);
    ans += a.get_str() + " ";
  }

  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "花费了"
            << double(duration.count()) *
                   std::chrono::microseconds::period::num /
                   std::chrono::microseconds::period::den
            << "秒" << std::endl;
  std::cout << "加密完成,得到密文为: " << std::endl;
  std::cout << ans << std::endl;
  std::cout << "写入文件: " << out << std::endl;
  std::ofstream file;
  file.open(out);
  file << ans;
  file.close();
}
void Rsa::decrypt(std::string filename, std::string out) {
  // 读取文件到string
  std::cout << "请输入N: ";
  std::cin >> n;
  std::cout << "请输入private_key: ";
  std::cin >> private_key;
  std::ifstream f(filename);
  std::stringstream s;
  s << f.rdbuf();
  f.close();
  // 密文拆分
  std::vector<std::string> ciphertext_string;
  std::vector<Bigint> ciphertext_gz;
  String_Split(s.str(), ' ', ciphertext_string);
  int length = ciphertext_string.size(); // 字符个数
  // cout << "字符个数为: " << length << endl;  //test

  // 类型转换string to mpz_class
  for (int i = 0; i < length; i++) {
    Bigint temp;
    temp.set_str(ciphertext_string[i], 0);
    // cout << temp << endl;
    ciphertext_gz.push_back(temp);
    // cout << ciphertext_gz[i] << endl;  //test
  }

  // 解密
  std::string DecryptedText;
  std::cout << "解密中...\n";
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < length; i++) {
    Bigint c = ciphertext_gz[i];       // 提取密文
    Bigint m = pow(c, private_key, n); // 解密
    DecryptedText.append(1, static_cast<unsigned char>(m.get_ui()));
    // cout << "目前已解密明文为:\n" << DecryptedText << endl;  //test
  }

  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "花费了"
            << double(duration.count()) *
                   std::chrono::microseconds::period::num /
                   std::chrono::microseconds::period::den
            << "秒" << std::endl;
  std::cout << "解密后明文: \n";
  std::cout << DecryptedText;
  std::cout << "写入文件: " << out << std::endl;
  std::ofstream file;
  file.open(out);
  file << DecryptedText;
  file.close();
}
