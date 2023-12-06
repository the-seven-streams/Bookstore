#include"Processtxt.hpp"
using std::string;

string ProcessTxt(string &txt) {
  while(txt[0] == ' ') {
    txt.erase(0, 1);
  }
  while(txt[txt.size() - 1] == ' ') {
    txt.erase(txt.size() - 1, 1);
  }
  string tmp;
  int i = 0;
  while(txt[0] != ' ' && (!txt.empty())) {
    tmp += txt[0];
    txt.erase(0, 1);
    i++;
  }
  return tmp;
}