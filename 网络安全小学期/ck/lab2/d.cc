#include "cmdline.h"
#include "des.h"
#include <chrono>
#include <string>
int main(int argc, char *argv[]) {
  // 解析参数
  cmdline::parser a;
  a.add<std::string>("input", 'i', "inputfile", true, "");
  a.add<std::string>("output", 'o', "outputfile", true, "");
  a.add("e", '\0', "encrypt");
  a.add("d", '\0', "decrypt");
  a.parse_check(argc, argv);
  if (!a.exist("e") && !a.exist("d")) {
    std::cout << "choose mode: enc or dec" << std::endl;
    std::cout << a.usage();
    return 0;
  }
  std::string in = a.get<std::string>("input");
  std::string out = a.get<std::string>("output");

  // 加密
  if (a.exist("e")) {
    std::cout << "加密开始" << std::endl;
    Des d;

    auto start = std::chrono::system_clock::now();
    d.encrypt(in, out);
    auto end = std::chrono::system_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "花费了"
              << double(duration.count()) *
                     std::chrono::microseconds::period::num /
                     std::chrono::microseconds::period::den
              << "秒" << std::endl;
  } else if (a.exist("d")) {

    std::cout << "解密开始" << std::endl;
    Des d;

    auto start = std::chrono::system_clock::now();
    d.decrypt(in, out);
    auto end = std::chrono::system_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "花费了"
              << double(duration.count()) *
                     std::chrono::microseconds::period::num /
                     std::chrono::microseconds::period::den
              << "秒" << std::endl;
  } else {
    std::cout << a.usage() << std::endl;
  }
  return 0;
}
