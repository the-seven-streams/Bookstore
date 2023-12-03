#include"Account.hpp"
#include<bits/stdc++.h>
using std::fstream;
using std::string;

extern std::stack<Account> status;
int current_power = 0;

Account::Account() {
  memset(userid, 0, sizeof(userid));
  memset(password, 0, sizeof(password));
  memset(username, 0, sizeof(username));
  power = 0;
  used = false;
}
Account::~Account() = default;

void Account::Setroot() {
  userid[0] = 'r';
  userid[1] = 'o';
  userid[2] = 'o';
  userid[3] = 't';
  password[0] = 's';
  password[1] = 'j';
  password[2] = 't';
  password[3] = 'u';
  power = 7;
  used = true;
}


void Initital() {
  fstream file;
  string txt = "Account.txt";
  if (access(txt.c_str(), F_OK) == 0) {//文件已经被创建。
      return;
    }
  Account root;
  root.Setroot();  
  file.open(txt);
  int num = 1;
  file.write(reinterpret_cast<char *>(&num), sizeof(int));//记录已经有多少账号
  file.seekp(4);
  file.write(reinterpret_cast<char *>(&root), sizeof(Account));
  status.push(root);
  file.close();
  current_power = 7;
  return;
}