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
  void Setroot(); // done.
  // This function is to set the root account.
  void SetuserID(char *); // done.
  // This function is to set the user id.
  void Setpassword(char *); // done.
  // This function is to set the password.
  int Getpower(); // done.
  // This function is to get the power of the account.
  void Right(char *); // done.
  // This function is to check whether the password is right.
  bool operator<(const Account &) const;
  bool operator>(const Account &) const;
  bool operator==(const Account &) const;

  friend void Register(char *, char *, char *); // done.
  // This function is to register a new account.
  friend void ChangePassword(char *, char *, char *);//done.
  friend void DeleteAccount(char *);//done.
  friend void Addaccount(char *, char *, char *, char *);//done;
};
void Register(char *, char *, char *); // done.
void ChangePassword(char *, char *, char *);//done.
void DeleteAccount(char *);//done.
void Addaccount(char *, char *, char *, char *);//done;
void Initital();
// This function is to initialize the system.
#endif