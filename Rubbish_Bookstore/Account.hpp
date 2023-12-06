#include<bits/stdc++.h>
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
class Account {
private:
  char userid[31];
  char password[31];
  char username[31];
  int power;
public:
  Account();
  Account(std::string);
  ~Account();
  void Register(char*, char*, char*);//done.
  //This function is to register a new account.
  void ChangePassword(char*, char*);
  void DeleteAccount();
  void Addaccount();
  void Setroot();//done.
  //This function is to set the root account.
  void SetuserID(char*);//done.
  //This function is to set the user id.
  void Setpassword(char*);//done.
  //This function is to set the password.
  int Getpower();//done.
  //This function is to get the power of the account.
  void Right(char*);//done.
  //This function is to check whether the password is right.
  bool operator<(const Account &);
  bool operator>(const Account &);
  bool operator==(const Account &);  
};
void Initital();
//This function is to initialize the system.
#endif