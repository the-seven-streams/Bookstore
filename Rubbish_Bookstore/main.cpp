#include "Account.hpp"
#include "Accountstatus.hpp"
#include "Book.hpp"
#include "Check.hpp"
#include "Processtxt.hpp"
#include "Rubbishaccountstore.hpp"
#include "Store.hpp"
#include <bits/stdc++.h>
#include <string>
using std::cin;
using std::getline;
using std::string;
extern int current_power;
extern std::stack<string> selected;
extern Book an_empty_book;
extern KeyBook an_empty_keybook;
Store<Book> book_main("book_main.txt");
Store<KeyBook> book_author("book_author.txt");
Store<KeyBook> book_name("book_name.txt");
Store<KeyBook> book_keyword("book_keyword.txt");
int main() {
  char *tmp;
  string txt;
  Initital();
  while (1) {
    try {
      getline(cin, txt);
      string command = ProcessTxt(txt); // 捕获第一条指令。
      if (command == "") {
        continue;
      }
      if (command == "su") {
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        string password = ProcessTxt(txt); // 捕获密码。
        CheckEmpty(txt);
        Login(const_cast<char *>(id.c_str()),
              const_cast<char *>(password.c_str()));
        continue;
      }
      if (command == "logout") {
        if (current_power == 0) {
          throw(0);
        }
        CheckEmpty(txt);
        Logout();
        continue;
      }
      if (command == "register") {
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        string password = ProcessTxt(txt); // 捕获密码。
        if (password.empty()) {
          throw(0);
        }
        string name = ProcessTxt(txt); // 捕获姓名。
        if (name.empty()) {
          throw(0);
        }
        CheckEmpty(txt);
        Register(const_cast<char *>(id.c_str()),
                 const_cast<char *>(password.c_str()),
                 const_cast<char *>(name.c_str()));
        continue;
      }
      if (command == "passwd") {
        if (current_power == 0) {
          throw(0);
        }
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        string oldpassword = ProcessTxt(txt); // 捕获旧密码。
        if (oldpassword.empty()) {
          throw(0);
        }
        string newpassword = ProcessTxt(txt); // 捕获新密码。
        CheckEmpty(txt);
        ChangePassword(const_cast<char *>(id.c_str()),
                       const_cast<char *>(oldpassword.c_str()),
                       const_cast<char *>(newpassword.c_str()));
        continue;
      }
      if (command == "useradd") {
        if (current_power < 3) {
          throw(0);
        }
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        string password = ProcessTxt(txt); // 捕获密码。
        if (password.empty()) {
          throw(0);
        }
        string power = ProcessTxt(txt); // 捕获权限。
        if (power.empty()) {
          throw(0);
        }
        string name = ProcessTxt(txt); // 捕获姓名。
        if (name.empty()) {
          throw(0);
        }
        CheckEmpty(txt);
        Addaccount(const_cast<char *>(id.c_str()),
                   const_cast<char *>(password.c_str()),
                   const_cast<char *>(power.c_str()),
                   const_cast<char *>(name.c_str()));
        continue;
      }
      if (command == "delete") {
        if (current_power != 7) {
          throw(0);
        }
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        CheckEmpty(txt);
        DeleteAccount(const_cast<char *>(id.c_str()));
        continue;
      }
      if (command == "quit") {
        if (!txt.empty()) {
          throw(0);
        }
        exit(0);
      }
      if (command == "exit") {
        if (!txt.empty()) {
          throw(0);
        }
        exit(0);
      }
      throw(0);     // 捕获无效指令。
    } catch (int) { // 针对程序中出现的所有问题进行捕获。
      std::cout << "Invalid\n";
    }
  }
  return 0;
}