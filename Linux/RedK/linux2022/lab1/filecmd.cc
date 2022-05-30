/* some commands about the file system
 * rm - remove a file
 * mkdir - make a directory
 * cd - change directory
 * pwd - print the current directory
 * cat - concatenate files
 * ls - list files in a directory
 * wc - count lines, words, and characters in a file
 */
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "shell.h"
using namespace std;
// remove files
void Shell::rm() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (std::remove(args[i].c_str()) != 0)
      std::cout << "rm: cannot remove '" << args[i] << "'" << std::endl;
  }
}

// make a directory by c++ 17
void Shell::mkdir() {
  print_reset();
  for (int i = 1; i < args.size(); i++) {
    if (std::filesystem::create_directory(args[i]))
      std::cout << "mkdir: cannot create '" << args[i] << "'" << std::endl;
  }
}

// show the current directory
void Shell::pwd() {
  print_reset();
  std::cout << std::filesystem::current_path() << std::endl;
}

// change the current directory
void Shell::cd() {
  print_reset();
  // if redirect flag is set, redirect the output to the file
  //if (re
  if (args.size() == 1) {
    std::cout << "cd dir" << std::endl;
    return;
  }
  try {
    std::filesystem::current_path(args[1]);
  } catch (std::filesystem::filesystem_error& e) {
    std::cout << "cd: cannot change directory to '" << args[1] << "'"
              << std::endl;
  }
}
// ls - list the files in the current directory
void Shell::ls() {
  print_reset();
  // ls
  if (args.size() == 1) {
    for (auto& p : std::filesystem::directory_iterator(".")) {
      std::cout << p.path().filename() << std::endl;
    }
  }
  // ls -l

  // ls -a
  else if (args.size() == 2 && args[1] == "-a") {
    for (auto& p : std::filesystem::directory_iterator(".")) {
      std::cout << p.path().filename() << std::endl;
    }
  }
  // ls dir
  else if (args.size() == 2) {
    try {
      for (auto& p : std::filesystem::directory_iterator(args[1])) {
        std::cout << p.path().filename() << std::endl;
      }
    } catch (std::filesystem::filesystem_error& e) {
     std::cout << "ls: invalid option" << std::endl;
    }
  }
 
}

// wc - count the lines, words and characters in a file
void Shell::wc() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "wc file" << std::endl;
    return;
  }
  std::ifstream in(args[1]);
  if (!in) {
    std::cout << "wc: cannot open '" << args[1] << "'" << std::endl;
    return;
  }
  int lines = 0;
  int words = 0;
  int chars = 0;
  std::string line;
  while (std::getline(in, line)) {
    lines++;
    words += std::count(line.begin(), line.end(), ' ');
    chars += line.size();
  }
  std::cout <<"lines : " <<lines <<endl<<"words : " << words <<endl<< "chars : " << chars << std::endl;
}

// cat - concatenate files and print on the standard output
void Shell::cat() {
  print_reset();
  if (args.size() == 1) {
    std::cout << "cat file" << std::endl;
    return;
  }
  // cat -n
  if (args.size() == 2 && args[1] == "-n") {
    std::ifstream in(args[2]);
    if (!in) {
      std::cout << "cat: cannot open '" << args[2] << "'" << std::endl;
      return;
    }
    int line = 1;
    std::string line_str;
    while (std::getline(in, line_str)) {
      std::cout << line << " " << line_str << std::endl;
      line++;
    }
  }
  // cat file
  else if (args.size() == 2) {
    std::ifstream in(args[1]);
    if (!in) {
      std::cout << "cat: cannot open '" << args[1] << "'" << std::endl;
      return;
    }
    std::string line;
    while (std::getline(in, line)) {
      std::cout << line << std::endl;
    }
  }
}
