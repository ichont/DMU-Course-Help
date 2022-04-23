/*
 * the file defines some functions about print 
 *  print_prompt : print the prompt
 *  welcome : print the welcome message
 *  print_reset : reset color
 *  help : print the help message
 */
#include "shell.h"
#include <iostream>
#include <string>
using namespace std;

#define reset_color "\033[0m"

//  reset_color for command after prompt
void Shell::print_prompt() {
    cout <<  prompt_color << prompt_text<< command_color;
    // advoid copy
    num++;
    joke();
}

void Shell::welcome() {
  cout << wlcolor << wltext << endl;
}

// reset_color for print
void Shell::print_reset() {
  cout << command_color;
}

// help 
void Shell::help() {
  cout <<"-------------------------------------------------------"<<endl;
  cout << "COMD\t\t\tUSEG\t\t\tARGS" << endl;
  cout << "-------------------------------------------------------"<<endl;
  cout << "clear\t\t\tclear screen\t\t" << endl;
  cout << "echo\t\t\techo chars\t\tchars" << endl;
  cout << "exit\t\t\texit shell\t\t" << endl;
  cout << "help\t\t\tcomd help\t\t\t" << endl;
  cout << "history\t\t\tcomd history\t\t" << endl;
  cout << "pwd\t\t\tshow current path\t\t" << endl;
  cout << "cd\t\t\tchange directory\tpath" << endl;
  cout << "ls\t\t\tlist directory\t\ta/l/path" << endl;
  cout << "cat\t\t\tcat file\t\tfile" << endl;
  cout << "wc\t\t\tcount chars\t\tfile" << endl;
  cout << "mkdir\t\t\tmake directory\t\tpath" << endl;
  cout << "rm\t\t\tremove file\t\tfile" << endl;

}
// 

