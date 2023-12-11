#include"Log.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
MemoryRiver<Operation, 1> logdata("Log.txt");

void Initial(Operation &op) {
  op.author = false;
  op.ISBN_ = false;
  op.name = false;
  op.keyword = false;
  op.price = false;
  op.value = 0;
  memset(op.command, 0, sizeof(op.command));
  memset(op.ISBN, 0, sizeof(op.ISBN));
  memset(op.id, 0, sizeof(op.id));
  op.user = Account();
  return;
}

void Print(Operation &op) {
  std::cout << op.command << " ";//说明操作类型。
  std::cout << "operated by " << op.user.GetID() << ".";//说明操作者。
  if(strcmp(op.command, "logout") == 0) {
    return;
  }
  if((strcmp(op.command, "su") == 0)||(strcmp(op.command, "register") == 0)
  ||(strcmp(op.command, "delete") == 0)||(strcmp(op.command, "passwd") == 0) ||
  (strcmp(op.command, "useradd") == 0)) {
    cout << "The Target Account is " << op.id << ".\n";//说明操作对象。
    return;
  }
  if((strcmp(op.command, "select") == 0)||(strcmp(op.command, "modify") == 0)) {
    cout << "The Target Book is " << op.ISBN << ".";//说明操作对象。
    if(strcmp(op.command, "modify") == 0) {
      cout << "The Target Book is modified with";
      if(op.author) {
        cout << " author";//说明操作对象。
      }
      if(op.ISBN_) {
        cout << " ISBN";//说明操作对象。
      }
      if(op.name) {
        cout << " name";//说明操作对象。
      }
      if(op.keyword) {
        cout << " keyword";//说明操作对象。
      }
      if(op.price) {
        cout << " price";//说明操作对象。
      }
      cout << ".\n";
    }
    return;
  }
  if(strcmp(op.command, "show") == 0) {
    if(strlen(op.addtion) == 0) {
      cout  << "All Books are shown.\n";
      return;
    }
    if(op.author) {
      cout << "Books with author " << op.addtion << " are shown.\n";
      return;
    }
    if(op.ISBN_) {
      cout << "Books with ISBN " << op.addtion << " are shown.\n";
      return;
    }
    if(op.name) {
      cout << "Books with name " << op.addtion << " are shown.\n";
      return;
    }
    if(op.keyword) {
      cout << "Books with keyword " << op.addtion << " are shown.\n";
      return;
    }
  }
  if(strcmp(op.command, "buy") == 0) {
    cout << op.quantity << " book(s) " << op.ISBN << " is sold with " << op.value << ".\n";
    return;
  }
  if(strcmp(op.command, "import") == 0) {
    cout << op.quantity << " book(s) " << op.ISBN << " is imported with " << op.value << ".\n";
    return;
  }
  return;
}

void Log() {
  cout << "**********Log Report**********\n";
  int total;
  logdata.get_info(total, 1);//获取日志总数。
  Operation *op = new Operation[total];
  logdata.read(op[0], 4);
  for(int i = 0; i < total; i++) {
    Print(op[i]);
  }
  delete [] op;
  return;
}

void ReportFinance() {
  cout << "**********Finance Report**********\n";
  int total;
  logdata.get_info(total, 1);//获取日志总数。
  Operation *op = new Operation[total];
  logdata.read(op[0], 4);
  double buy = 0, import = 0;
  for(int i = 0; i < total; i++) {
    if(strcmp(op[i].command, "buy") == 0) {
      buy += op[i].value;
      Print(op[i]);
    }
    if(strcmp(op[i].command, "import") == 0) {
      import += op[i].value;
      Print(op[i]);
    }
  }
  delete[] op;
  cout << "Total Profit: " << 
  std::fixed << std::setprecision(2) << import - buy << ".\n";
  return;
}

void ReportEmployee() {
  cout << "**********Employee Report**********\n";
  int total;
  logdata.get_info(total, 1);//获取日志总数。
  Operation *op = new Operation[total];
  logdata.read(op[0], 4);
  for(int i = 0; i < total; i++) {
    if(op[i].user.Getpower() < 3) {
      continue;
    }
    Print(op[i]);
  }
  delete[] op;
  return;
}