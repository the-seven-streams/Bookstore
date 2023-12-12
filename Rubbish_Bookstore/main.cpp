#include "Account.hpp"
#include "Accountstatus.hpp"
#include "Book.hpp"
#include "Check.hpp"
#include "Finance.hpp"
#include "Processtxt.hpp"
#include "Log.hpp"
#include "Store.hpp"
#include <bits/stdc++.h>
#include <cassert>
#include <cstring>
#include <string>
using std::cin;
using std::getline;
using std::string;
extern int current_power;
extern std::vector<Book> selected;
extern Book an_empty_book;
extern KeyBook an_empty_keybook;
extern std::stack<Account> status;
extern double Buy(char *, int);
Store<Book> book_main("book_main.txt");
Store<KeyBook> book_author("book_author.txt");
Store<KeyBook> book_name("book_name.txt");
Store<KeyBook> book_keyword("book_keyword.txt");
extern Store<Account> account;
extern MemoryRiver<Operation, 1> logdata;
double total_cost = 0;
double total_income = 0;
Operation recorder;

int main() {
  char *tmp;
  string txt;
  string res;
  Initital();
  while (!cin.eof()) {
    try {
      InitialOp(recorder);
      getline(cin, res);
      txt = res;
      string command = ProcessTxt(txt); // 捕获第一条指令。
      if (command == "") {
        continue;
      }
      if (command == "su") {
        if(!status.empty()) {
          recorder.user = status.top();
        }
        string id = ProcessTxt(txt); // 捕获用户名。
        if (id.empty()) {
          throw(0);
        }
        string password = ProcessTxt(txt); // 捕获密码。
        CheckEmpty(txt);
        Login(const_cast<char *>(id.c_str()),
              const_cast<char *>(password.c_str()));
        strcpy(recorder.command, "su");
        strcpy(recorder.id, id.c_str()); 
        AddLog(recorder);
        continue;
      }
      if (command == "logout") {
        if(status.empty()) {
          throw(0);
        }
        recorder.user = status.top();
        if (current_power == 0) {
          throw(0);
        }
        CheckEmpty(txt);
        Logout();
        strcpy(recorder.command, "logout");
        AddLog(recorder);
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
        if(!status.empty()) {
          recorder.user = status.top();
        } else {
          recorder.user = Account();
        }
        strcpy(recorder.command, "register");
        strcpy(recorder.id, id.c_str());
        AddLog(recorder);
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
        recorder.user = status.top();
        strcpy(recorder.command, "passwd");
        strcpy(recorder.id, id.c_str());
        AddLog(recorder);
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
        recorder.user = status.top();
        strcpy(recorder.command, "useradd");
        strcpy(recorder.id, id.c_str());
        AddLog(recorder);
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
        recorder.user = status.top();
        strcpy(recorder.command, "delete");
        strcpy(recorder.id, id.c_str());
        AddLog(recorder);
        continue;
      }
      if (command == "quit") {
        if (!txt.empty()) {
          throw(0);
        }
        book_main.UpdateIndex();
        book_author.UpdateIndex();
        book_name.UpdateIndex();
        book_keyword.UpdateIndex();
        account.UpdateIndex();
        exit(0);
      }
      if (command == "exit") {
        if (!txt.empty()) {
          throw(0);
        }
        book_main.UpdateIndex();
        book_author.UpdateIndex();
        book_name.UpdateIndex();
        book_keyword.UpdateIndex();
        account.UpdateIndex();
        exit(0);
      }
      if (command == "select") {
        if (current_power < 3) {
          throw(0);
        }
        string ISBN = ProcessTxt(txt); // 捕获ISBN。
        if (ISBN.empty()) {
          throw(0);
        }
        CheckEmpty(txt); // 检查是否有冗余参数。
        Select(const_cast<char *>(ISBN.c_str()));
        recorder.user = status.top();

        strcpy(recorder.command, "select");
        strcpy(recorder.ISBN, ISBN.c_str());
        AddLog(recorder);
        continue;
      }
      if (command == "show") {
        if (!current_power) {
          throw(0);
        }
        string addtion = ProcessTxt(txt);
        if (addtion == "finance") {
          if (current_power < 7) {
            throw(0);
          }
          string n = ProcessTxt(txt);
          CheckEmpty(txt);
          if (n.empty()) {
            ShowFinance(0);
            continue;
          }
          CheckN(const_cast<char *>(n.c_str()));
          int num = atoi(const_cast<char *>(n.c_str()));
          if (num < 0) {
            throw(0);
          }
          if (num == 0) {
            cout << std::endl;
            continue;
          }
          ShowFinance(num);
          recorder.user = status.top();
          strcpy(recorder.command, "showfinance");
          AddLog(recorder);
          continue;
        }
        if (addtion.empty()) {
          Showall();
          recorder.user = status.top();
          strcpy(recorder.command, "show");
          strcpy(recorder.addtion, "");
          AddLog(recorder);
          continue;
        }
        if (addtion[0] != '-') {
          throw(0);
        }                    // 删除必然存在的减号。
        addtion.erase(0, 1); // 删除减号。
        if (addtion.empty()) {
          throw(0);
        } // 弟啊，你参数呢。
        Processshow(addtion);
        recorder.user = status.top();
        strcpy(recorder.command, "show");
        strcpy(recorder.addtion, addtion.c_str());
        AddLog(recorder);
        continue;
      }
      if (command == "modify") {
        if (current_power < 3) {
          throw(0);
        }
        if (txt.empty()) {
          throw(0);
        }
        if (selected.back() == an_empty_book) {
          throw(0);
        } // 未选中书目。
        strcpy(recorder.ISBN, selected.back().GetISBN());
        selected.back().ModifyProcess(txt);
        recorder.user = status.top();
        strcpy(recorder.command, "modify");
        AddLog(recorder);
        continue;
      }
      if (command == "import") {
        if (current_power < 3) {
          throw(0);
        }
        if (selected.back() == an_empty_book) {
          throw(0);
        } // 未选中书目。
        string quantity = ProcessTxt(txt);
        CheckSize10(const_cast<char *>(quantity.c_str()));
        if (quantity.empty()) {
          throw(0);
        }
        CheckN(const_cast<char *>(quantity.c_str()));
        string cost = ProcessTxt(txt);
        if (cost.empty()) {
          throw(0);
        }
        CheckSize13(const_cast<char *>(cost.c_str()));
        CheckReal(const_cast<char *>(cost.c_str()));
        int q = atoi(const_cast<char *>(quantity.c_str()));
        double c = atof(const_cast<char *>(cost.c_str()));
        if (q <= 0) {
          throw(0);
        }
        if (c <= 0) {
          throw(0);
        }
        CheckEmpty(txt);
        selected.back().Import(q);
        total_cost += c;
        AddDeal(-c);
        recorder.user = status.top();
        strcpy(recorder.command, "import");
        recorder.quantity = q;
        recorder.value = c;
        strcpy(recorder.ISBN, selected.back().GetISBN());
        AddLog(recorder);
        continue;
      }
      if (command == "buy") {
        if (!current_power) {
          throw(0);
        }
        string isbn = ProcessTxt(txt);
        if (isbn.empty()) {
          throw(0);
        }
        CheckSize20(const_cast<char *>(isbn.c_str()));
        CheckVisible(const_cast<char *>(isbn.c_str()));
        string num = ProcessTxt(txt);
        if (num.empty()) {
          throw(0);
        }
        CheckSize10(const_cast<char *>(num.c_str()));
        CheckN(const_cast<char *>(num.c_str()));
        int n = atoi(const_cast<char *>(num.c_str()));
        double value = Buy(const_cast<char *>(isbn.c_str()), n);
        CheckEmpty(txt);
        total_income += value;
        AddDeal(value);
        recorder.user = status.top();
        strcpy(recorder.command, "buy");
        recorder.quantity = n;
        recorder.value = value;
        strcpy(recorder.ISBN, isbn.c_str());
        AddLog(recorder);
        continue;
      }
      if(command == "log") {
        if(current_power < 7) {
          throw(0);
        }
        CheckEmpty(txt);
        Log();
        continue;
      }
      if(command == "report") {
        if(current_power < 7) {
          throw(0);
        }
        string addtion = ProcessTxt(txt);
        if(addtion == "finance") {
          CheckEmpty(txt);
          ReportFinance();
          continue;
        }
        if(addtion == "employee") {
          CheckEmpty(txt);
          ReportEmployee();
          continue;
        }
        throw(0);
      }
      throw(0);     // 捕获无效指令。
    } catch (int) { // 针对程序中出现的所有问题进行捕获。
      std::cout << "Invalid\n";
    }
  }
  book_main.UpdateIndex();
  book_author.UpdateIndex();
  book_name.UpdateIndex();
  book_keyword.UpdateIndex();
  account.UpdateIndex();
  return 0;
}