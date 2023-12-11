#include<bits/stdc++.h>
#ifndef Log_hpp
#define Log_hpp
#include"Account.hpp"
#include"Store.hpp"
struct Operation{
  Account user;
  char command[20];
  char ISBN[21];
  char id[31];
  bool author;
  bool ISBN_;
  bool name;
  bool keyword;
  bool price;
  double value;
  int quantity;
  char addtion[61];
};
void InitialOp(Operation &);
void Print(Operation &);
void Log();
void ReportFinance();
void ReportEmployee();
void AddLog(Operation &);
#endif