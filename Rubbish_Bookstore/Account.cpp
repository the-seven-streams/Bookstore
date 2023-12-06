#include"Account.hpp"
#include"Rubbishaccountstore.hpp"
#include<bits/stdc++.h>
#include <cstring>
#include"Check.hpp"
using std::fstream;
using std::string;

extern std::stack<Account> status;
extern std::multiset<Account> used;
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

void Register(char *id, char *pwd, char *name) {
  CheckNLU(id);//检查内容合法性。
  CheckNLU(pwd);
  Account tmp;
  tmp.SetuserID(id);
  if(RubbishAccount::Find(tmp) == tmp) {
    throw(0);
  }//说明该账户已经被注册。
  tmp.Setpassword(pwd);
  tmp.power = 1;
  strcpy(tmp.username, name);
  RubbishAccount::Insert(tmp);
  return;
}

void ChangePassword(char *id, char *old_pw, char *new_pw) {
  Account tmp;
  tmp.SetuserID(id);
  Account to_change;
  to_change = RubbishAccount::Find(tmp);
  if(!(to_change == tmp)) {
    throw(0);
  }//说明没有找到，无法修改密码。
  if(strlen(new_pw) == 0) {
    if(current_power != 7) {
      throw(0);//没有权限。不可以执行该操作。
    }
    to_change.Setpassword(old_pw);//修改密码。
    RubbishAccount::Delete(to_change);
    RubbishAccount::Insert(to_change);
  }else {
    to_change.Right(old_pw);//如果密码错误，即退出。
    to_change.Setpassword(new_pw);//修改密码。
    RubbishAccount::Delete(to_change);
    RubbishAccount::Insert(to_change);
  }
  return;
}

void DeleteAccount(char *id) {
  Account tmp;
  tmp.SetuserID(id);
  if(!(RubbishAccount::Find(tmp) == tmp)) {
    throw(0);
  }//说明没有找到，无法删除。
  if(used.find(tmp) != used.end()) {
    throw(0);
  }//说明该账户正在被使用，无法删除。
  RubbishAccount::Delete(tmp);
  return;
}

void Addaccount(char *id, char *pw, char *pr, char *name) {
  CheckNLU(id);
  CheckNLU(pw);
  CheckN(pr);
  int len = strlen(pr);
  if(len != 0) {
    throw(0);
  }//说明权限输入错误。
  int num = pr[0] - '0';
  if(num >= current_power) {
    throw(0);
  }//当前权限不足。
  if(num!=1 && num!=3 && num!=7) {
    throw(0);
  }//权限不正确。
  Account tmp;
  tmp.SetuserID(id);
  if(RubbishAccount::Find(tmp) == tmp) {
    throw(0);
  }//说明该账户已经被注册。
  tmp.Setpassword(pw);
  tmp.power = pr[0] - '0';
  strcpy(tmp.username, name);
  RubbishAccount::Insert(tmp);
  return;
}


void Initital() {
  Account root;
  root.Setroot();  
  RubbishAccount::Insert(root);
  return;
}


bool Account::operator<(const Account &b) const {
  return strcmp(userid, b.userid) < 0;
}
bool Account::operator>(const Account &b) const {
  return strcmp(userid, b.userid) > 0;
}
bool Account::operator==(const Account &b) const {
  return strcmp(userid, b.userid) == 0;
}