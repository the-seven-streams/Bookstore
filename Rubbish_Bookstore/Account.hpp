#include<bits/stdc++.h>
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
class Account {
private:
  char userid[31];
  char password[31];
  char username[31];
  int power;
  bool used;
public:
  Account();
  ~Account();
  void Register();
  void ChangePassword();
  void DeleteAccount();
  void SignUp();
  bool Isusing();
  void Setroot();
  int Getpower();
};
void Initital();
#endif