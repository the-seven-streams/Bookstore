#include<bits/stdc++.h>
#include"Account.hpp"
#include"Check.hpp"
#include"Accountstatus.hpp"
#include"Rubbishaccountstore.hpp"
#include"Processtxt.hpp"
using std::string;
using std::cin;
using std::getline;

int main() {
  char *tmp;
  string txt;
  while(1) {
    try{
      getline(cin, txt);
      string command = ProcessTxt(txt);//捕获第一条指令。
      if(command == "su") {
        string username = ProcessTxt(txt);//捕获用户名。
        string password = ProcessTxt(txt);//捕获密码。
        Rubbishaccountstore::Login(username, password);//登录。
    }catch(int){//针对程序中出现的所有问题进行捕获。
      std::cout << "Invalid\n";
    }
  }
}