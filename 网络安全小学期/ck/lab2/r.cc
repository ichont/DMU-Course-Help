#include "cmdline.h"
#include "rsa.h"
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
    Rsa d;
    d.encryption(in, out);
  } else if (a.exist("d")) {

    Rsa d;
    d.decrypt(in, out);
  } else {
    std::cout << a.usage() << std::endl;
  }
  return 0;
}
