#include<bits/stdc++.h>
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
class Account {
private:
  char userid[31];
  char password[31];
  char username[31];
public:
  Account();
  ~Account();
  void Login(char*);
  void Register();
  void ChangePassword();
  void DeleteAccount();
  void SignUp();
};
#endif