#include <bits/stdc++.h>
#ifndef Log_hpp
#define Log_hpp
#include "Account.hpp"
#include "Store.hpp"
struct Operation {
  Account user;
  char command[20];
  char ISBN[21];
  char id[31];
  bool author;
  bool ISBN_;
  bool name;
  bool keyword;
  bool price;
  long double value;
  int quantity;
  char addtion[61];
};
void InitialOp(Operation &); // 初始化记录。
void Print(Operation &);     // 将记录的内容打印。
void Log();                  // 输出所有日志。
void ReportFinance();        // 输出财务报告。
void ReportEmployee();       // 输出员工工作情况。
void AddLog(Operation &);    // 添加日志。
#endif