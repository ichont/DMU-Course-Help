/*
 * the file defines some functions for the runtime for shell
 * Shell - constructor for the shell
 * Shell::run - run the shell
 * Shell::run_once - run one command
 * Shell::init - initialize the shell
 * history - the history of the shell
 * add_history - add a command to the history
 */
#include <cstdio>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "shell.h"
using namespace std;
// constructor
// use map to store the command
Shell::Shell() {
  // add commands
  commands["clear"] = bind(&Shell::clear, this);
  commands["echo"] = bind(&Shell::echo, this);
  commands["exit"] = bind(&Shell::exit, this);
  commands["rm"] = bind(&Shell::rm, this);
  commands["pwd"] = bind(&Shell::pwd, this);
  commands["cd"] = bind(&Shell::cd, this);
  commands["mkdir"] = bind(&Shell::mkdir, this);
  commands["ls"] = bind(&Shell::ls, this);
  commands["cat"] = bind(&Shell::cat, this);
  commands["wc"] = bind(&Shell::wc, this);
  commands["help"] = bind(&Shell::help, this);
  commands["history"] = bind(&Shell::history, this);
  // init
  init();
}
// init shell
void Shell::init() {
  // read config file
  readconfig();
  clear();
  welcome();
  // check history file exist
  if (!filesystem::exists(history_file)) {
    // create history file
    ofstream ofs(history_file);
    ofs.close();
  }
}

// run
void Shell::run() {
  while (true) {
    print_prompt();
    // read command
    getline(cin, input);
    // if input is empty, continue
    if (input == "") {
      continue;
    }
    // & is first than >
    // if & is in the input, background
    if (input.find("&") != string::npos) {
      // cout << "background" << endl;
      background();
      continue;
    }

    // if > is in the input, redirect
    if (input.find(">") != string::npos) {
      // cout << "redirect" << endl;
      redirect();
      continue;
    }
    // parse input
    // if command in map , call it
    parse();
    if (commands.find(args[0]) != commands.end()) {
      commands[args[0]]();
      add_history(input);
    } else {
      cout << Red << "Command not found" << endl;
    }
  }
}

// run only once
void Shell::run_once() {
  // if input is empty, continue
  if (input == "") {
    return;
  }
  // parse input
  // if command in map , call it
  // if > is in the input, redirect
  if (input.find(">") != string::npos) {
    // cout << "redirect" << endl;
    redirect();
    return;
  }

  parse();
  if (commands.find(args[0]) != commands.end()) {
    commands[args[0]]();
  } else {
    cout << Red << "Command not found" << endl;
  }
}

// add command to history file
void Shell::add_history(string command) {
  // open history file
  ofstream ofs(history_file, ios::app);
  // write command to history file
  ofs << command << endl;
  // close history file
  ofs.close();
}
// read history file
void Shell::history() {
  // open history file
  ifstream ifs(history_file);
  // read line by line
  string line;
  while (getline(ifs, line)) {
    // add line to history
    cout << line << endl;
  }
  // close history file
  ifs.close();
}
/*
// deal arrow key
void Shell::arrow_key() {
  // if key is u
  if (key == KEY_UP) {
    // if history_index is 0, do nothing
    if (history_index == 0) {
      return;
    }
    // if history_index is not 0, minus 1
    history_index--;
    // get history command
    input = history_list[history_index];
    // print input
    cout << input << endl;
  }
  // if key is down
  if (key == KEY_DOWN) {
    // if history_index is history_list.size(), do nothing
    if (history_index == history_list.size()) {
      return;
    }
    // if history_index is not history_list.size(), plus 1
    history_index++;
    // get history command
    input = history_list[history_index];
    // print input
    cout << input << endl;
  }
}
*/
