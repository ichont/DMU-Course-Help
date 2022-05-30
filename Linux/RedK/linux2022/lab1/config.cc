/*
 * read config file and set global variables
 */
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "shell.h"
#include "tools.h"
using namespace std;

map<string, string> colors{
    {"black", "\033[30m"},  {"red", "\033[31m"},   {"green", "\033[32m"},
    {"yellow", "\033[33m"}, {"blue", "\033[34m"},  {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},   {"white", "\033[37m"}, {"reset", "\033[0m"}};
// readconfig
// reads the config file and sets the variables
// read by line
void Shell::readconfig() {
  // open the file
  ifstream config("config.ck");
  string line;
  // int a = 0;
  while (getline(config, line)) {
    // if the line is a comment or empty, ignore it
    // delete spaces
    // cout << "read line:" << a++ << "\b empty:" << line.empty() << endl;
    try {
      // first check if the line is a empty
      if (line.empty() || line[0] == '#') {
        continue;
      }
      // line = delete_first_space(line);
      if (line.find("=") != string::npos) {
        // read key
        string keystr = line.substr(0, line.find("="));
        delete_all_space(keystr);
        string key = keystr.substr(0, line.find("="));
        // read value
        string value = line.substr(line.find_first_of("\"")+1,
				   line.find_last_of("\"")-line.find_first_of("\"")-1);
        configmap[key] = value;
	//cout << "read key:" << key << " value:" << value << endl;
      }
    } catch (...) {
      cout << "Error reading config file" << endl;
    }
  }
  config.close();

  prompt_color = colors[configmap["PROMPT_COLOR"]];
  prompt_text = configmap["PROMPT_TEXT"];
  wlcolor =colors[configmap["WL_COLOR"]];
  wltext = configmap["WL_TEXT"];
  command_color = colors[configmap["CMD_COLOR"]];
  history_file = configmap["HIST_FILE"];
}
