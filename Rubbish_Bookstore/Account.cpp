#include"Account.hpp"
#include"Rubbishaccountstore.hpp"
#include<bits/stdc++.h>
#include <cstring>
#include"Check.hpp"
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

void Account::Right(char *pwd) {
  if(strcmp(password, pwd) != 0) {
    throw(0);
  }
  return;
}

void Account::Register(char *id, char *pwd, char *name) {
  CheckNLU(id);
  CheckNLU(pwd);
  this->SetuserID(id);
  if(RubbishAccount::Find(*this) == *this) {
    throw(0);
  }//说明该账户已经被注册。
  this->Setpassword(pwd);
  this->power = 1;
  strcpy(username, name);
  RubbishAccount::Insert(*this);
  return;
}


void Initital() {
  Account root;
  root.Setroot();  
  RubbishAccount::Insert(root);
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