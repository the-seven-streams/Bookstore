#include"Accountstatus.hpp"
#include"Account.hpp"
#include"Rubbishaccountstore.hpp"
using std::cout;
using std::cin;
using std::string;

std::stack<Account> status;
extern int current_power;

void Logout() {
  if(status.empty()) {
    cout << "Invalid\n";//没有任何账户可以登出。
  } else {
    status.pop();
    if(status.empty()) {
      current_power = 0;
    } else {
      current_power = status.top().Getpower();
    }
  }
  return;
}

void Login() {
  string txt;
  string id, pwd;
  std::getline(cin, txt);
}