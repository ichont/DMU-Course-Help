/* the file define some advanced functions for the shell
 * redirect - redirect the output of a command to a file
 * background - run a command in the background
 */
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include "shell.h"
#include "tools.h"

using namespace std;

// redirects stdout to a file
void Shell::redirect() {
   string his = input;
  // split by >
  vector<string> arg = split(input, '>');

  if (arg.size() == 2) {
    // delete space in the end
    delete_all_space(arg[1]);
    // redirect to file
    streambuf* buf = cout.rdbuf();
    ofstream out(arg[1]);
    cout.rdbuf(out.rdbuf());
    // run command
    input = arg[0];
    run_once();
    // add to history
    add_history(his);
    // refresh stdout stream
    cout.flush();
    // reset cout
    cout.rdbuf(buf);
  } else {
    cout << "Error: need 2 args" << endl;
  }
}
// run command in background
void Shell::background() {
  // split by &
  string his = input;
  vector<string> arg = split(input, '&');
  // run command in background
  pid_t pid = fork();
  if (pid == 0) {
    // run command
    input = arg[0];
    run_once();
    // add to history
    add_history(his);
    // get the pid of the child process
    int child_pid = getpid();
    cout << "run in background pid:" << child_pid << endl;
    std::exit(0);
  }
}
