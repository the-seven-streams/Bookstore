#include"Account.hpp"
#include"Rubbishaccountstore.hpp"
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
  Account root;
  root.Setroot();  
  RubbishAccount::Insert(root);
  return;
}
void Account::Register() {
  fstream file;
  string txt = "Account.txt";
  file.open(txt);
  file.seekg(0);
  int total;
  file.read(reinterpret_cast<char *>(&total), sizeof(int));//当前账号写入总数。
}

bool operator<(const Account &a, const Account &b) {
  return strcmp(a.userid, b.userid) < 0;
}
bool operator>(const Account &a, const Account &b) {
  return strcmp(a.userid, b.userid) > 0;
}
bool operator==(const Account &a, const Account &b) {
  return strcmp(a.userid, b.userid) == 0;
}
int main() {
  return 0;
}