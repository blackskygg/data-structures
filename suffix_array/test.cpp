#include "suffix_array.hpp"
#include "sys/time.h"
#include <string>
#include <iostream>
#include <ctime>

using namespace std;
string s("I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me."
         "I can eat glass, it doesn't hurt me.");

int main(int argc, char *argv[]) {
  DS::SuffixArray sa(s);
  string s1 = s.substr(s.size()/16);
  string s2 = s.substr(s.size()/8);
  string s3 = s.substr(s.size()/4);
  string s4 = s.substr(s.size()/2);

  if (argc != 2) {
    cout << "error." << endl;
    return -1;
  }

  int n = 1e6+0;
  if (argv[1][0] == '0') {
    while (n--) {
      sa.Match(s1);
      sa.Match(s2);
      sa.Match(s3);
      sa.Match(s4);
    }
  } else if (argv[1][0] == '1') {
    while (n--) {
      s.find(s1);
      s.find(s2);
      s.find(s3);
      s.find(s4);
    }
  } else {
    cout << "error." << endl;
    return -1;
  }

  return 0;
}
