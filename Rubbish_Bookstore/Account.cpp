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
  return;
}

void Account::SetuserID(char *id) {
  strcpy(userid, id);
  return;
}

void Account::Setpassword(char *pwd) {
  strcpy(password, pwd);
  return;
}

int Account::Getpower() {
  return power;
}

bool Account::Right(char *pwd) {
  return strcmp(password, pwd) == 0;
}

void Initital() {
  Account root;
  root.Setroot();  
  RubbishAccount::Insert(root);
  return;
}
void Account::Register() {
  fstream file;
  std::cin >> userid >> password >> username;
  power = 1;
  Account tmp = *this;
  RubbishAccount::Insert(tmp);
  return;
}

bool Account::operator<(const Account &b) {
  return strcmp(userid, b.userid) < 0;
}
bool Account::operator>(const Account &b) {
  return strcmp(userid, b.userid) > 0;
}
bool Account::operator==(const Account &b) {
  return strcmp(userid, b.userid) == 0;
}



int main() {
  int n;
  std::cin>>n;
  for(int i = 0; i < n; ++i) {
    Account tmp;
    tmp.Register();
    Account w = RubbishAccount::Find(tmp);
    std::cout << (w == tmp);
  }
  return 0;
}