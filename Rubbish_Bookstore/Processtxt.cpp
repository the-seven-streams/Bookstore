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
  while((!txt.empty()) && txt[0] != ' ') {
    tmp += txt[0];
    txt.erase(0, 1);
    i++;
  }
  return tmp;
}

string ProcessKey(string &txt) {
  string tmp;
  while((!txt.empty()) && txt[0] != '|') {
    tmp += txt[0];
    txt.erase(0, 1);
  }
  if(txt[0] == '|') {
    txt.erase(0, 1);
  }
  return tmp;
}