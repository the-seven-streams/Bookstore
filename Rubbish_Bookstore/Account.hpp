#include <bits/stdc++.h>
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include "Store.hpp"
class Account {
private:
  char userid[31];
  char password[31];
  char username[31];
  int power;

public:
  Account();
  ~Account();
  void Setroot(); //该函数用于初始化。能够设置root账户。
  void SetuserID(char *); //该函数用于设置用户id。
  void Setpassword(char *); //该函数用于设置密码。
  int Getpower(); //该函数用于获取权限。
  void Right(char *); //该函数用于检查密码正确性。
  bool operator<(const Account &) const;
  bool operator>(const Account &) const;
  bool operator==(const Account &) const;//账户之间的大小关系定义为用户id的字典序。

  friend void Register(char *, char *, char *);
  //实现注册功能。第一个参数为用户id，第二个参数为密码，第三个参数为用户名。
  friend void ChangePassword(char *, char *, char *);
  //实现修改密码功能。第一个参数为用户id，第二个参数为旧密码，第三个参数为新密码。
  //如果只有两个参数，那么第三个参数可缺省。
  friend void DeleteAccount(char *);
  //实现删除账户功能。第一个参数为用户id。
  friend void Addaccount(char *, char *, char *, char *);
  //实现添加账户功能。第一个参数为用户id，第二个参数为密码，第三个参数为权限，第四个参数为用户名。
};
void Register(char *, char *, char *);
void ChangePassword(char *, char *, char *);
void DeleteAccount(char *);
void Addaccount(char *, char *, char *, char *);
void Initital();//该函数用于初始化系统。即创建root账户。
#endif