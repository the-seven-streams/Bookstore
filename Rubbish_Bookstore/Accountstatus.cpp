#include "Accountstatus.hpp"
#include "Account.hpp"
#include "Book.hpp"
#include "Check.hpp"
#include "Store.hpp"
#include <cstring>
using std::string;
extern Store<Book> book_main;
extern Store<Account> account;
std::stack<Account> status;
std::vector<Book> selected;
std::multiset<Account> used;
extern int current_power;
extern Book an_empty_book;
extern KeyBook an_empty_keybook;
void Logout() {
  if (status.empty()) {
    throw(0); // 说明没有登录。
  } else {
    used.erase(used.find(status.top()));
    status.pop();
    selected.pop_back();
    if (status.empty()) {
      current_power = 0;
    } else {
      current_power = status.top().Getpower();
    }
  }
  return;
}

void Login(char *id, char *pwd = nullptr) {
  Account tmp;
  tmp.SetuserID(id);
  Account to_check;
  to_check = account.Find(tmp);
  if (!(to_check == tmp)) {
    throw(0); // 说明没有找到。
  }
  if (strlen(pwd)) {
    to_check.Right(pwd); // 如果密码错误，即退出。
  } else {
    if (current_power <= to_check.Getpower()) {
      throw(0); // 说明没有权限。
    }
  }
  status.push(to_check);
  used.insert(to_check);
  current_power = to_check.Getpower();
  selected.push_back(an_empty_book);
  return;
}
