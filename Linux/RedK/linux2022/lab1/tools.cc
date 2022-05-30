/*
 * some tools for shell commands
 * split function to split command line into tokens
 * extract_args function to extract args except command name
 *
 * some base functions for shell
 * echo function to print out args
 * exit function to exit shell
 * clear function to clear screen
 */
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "shell.h"
#include "tools.h"
using namespace std;

// parse args
// copy from
// https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string/237280#237280
template <typename Out>
void split(const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, item, delim)) {
    *result++ = item;
  }
}
std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

// find args except command
string extract_args(string input, string com) {
  size_t found = input.find(com);
  if (found != std::string::npos) {
    return input.substr(found + com.length() + 1);
  } else {
    return "";
  }
}

// delete the first space
string delete_first_space(string input) {
  size_t found = input.find_first_not_of(" ");
  if (found != std::string::npos) {
    return input.substr(found);
  } else {
    return "";
  }
}
// delete all spaces in the string
void delete_all_space(string &input) {
  input.erase(std::remove_if(input.begin(), input.end(),
                             [](unsigned char x) { return std::isspace(x); }),
              input.end());
}
// joke
void Shell::joke() {
  if (num > 4) {
      clear();
      // print a thumb
      cout << Red << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      cout << Red << "正义惩罚!要自己做题哦" << endl;
      cout << Red << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }


}
// parse input
void Shell::parse() {
  // delete_first_space
  string tmp = delete_first_space(this->input);
  args = split(tmp, ' ');
}
// clear shell
void Shell::clear() { cout << "\033[2J\033[1;1H"; }
// echo function
void Shell::echo() { 
        print_reset();
	cout << extract_args(input, "echo") << endl; }
// exit
void Shell::exit() {
  cout << "Bye!" << endl;
  // avoid name conflict
  std::exit(0);
}
