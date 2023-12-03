#include"Accountstatus.hpp"
using std::cout;

std::stack<Account> status;
extern int current_power;

void Logout() {
  if(status.empty()) {
    cout << "YOU IDIOT! YOU ARE NOT LOGINED!\n";
  } else {
    status.pop();
    current_power = status.top().Getpower();
  }
  return;
}

void Login() {
  
}