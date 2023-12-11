#include<bits/stdc++.h>
#ifndef Log_hpp
#define Log_hpp
#include"Accout.hpp"
#include"Store.hpp"
struct Operation{
  Account user;
  char command[10];
  char ISBN[20];
  char id[30];
  bool author;
  bool ISBN_;
  bool name;
  bool keyword;
  bool price;
  double value;
  void Print();
  void PrintEmployee();
  void PrintFinance();
};
#endif