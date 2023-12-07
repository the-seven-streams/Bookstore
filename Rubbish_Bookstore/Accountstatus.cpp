#include"Accountstatus.hpp"
#include"Account.hpp"
#include"Rubbishaccountstore.hpp"
#include"Check.hpp"
#include <cstring>
#include"Book.hpp"
#include"Store.hpp"
using std::string;
extern Store<Book> book_main;
std::stack<Account> status;
std::stack<string> selected;
std::multiset<Account> used;
extern int current_power;

void Logout() {
  if(status.empty()) {
    throw(0);//说明没有登录。
  } else {
    used.erase(used.find(status.top()));
    status.pop();
    selected.pop();
    if(status.empty()) {
      current_power = 0;
    } else {
      current_power = status.top().Getpower();
    }
  }
  return;
}

void Login(char* id, char* pwd = nullptr) {
  Account tmp;
  tmp.SetuserID(id);
  Account to_check;
  to_check = RubbishAccount::Find(tmp);
  if(!(to_check == tmp)) {
    throw(0);//说明没有找到。
  }
  if(strlen(pwd)) {
    to_check.Right(pwd);//如果密码错误，即退出。
  } else {
    if(current_power <= to_check.Getpower()) {
      throw(0);//说明没有权限。
    }
  }
  status.push(to_check);
  selected.push("");
  used.insert(to_check);
  current_power = to_check.Getpower();
  return;
}

void Select(char *isbn) {
  CheckSize20(isbn);
  CheckVisible(isbn);
  selected.pop();
  selected.push(isbn);
  return;
}