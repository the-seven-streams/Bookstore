#include<bits/stdc++.h>
#include"Account.hpp"
#ifndef ACCOUNTSTORE_HPP
#define ACCOUNTSTORE_HPP
class ElementAccount {//这一部分不需要在意。存储所需。
private:
  int size;        
  int block_place; 
  int block_nxt;  

public:
  Account user;
  ElementAccount() = default;
  void Setsize(int);
  int Getsize();
  int Getplace();
  void Setplace(int);
  int Getblock_nxt();
  void Setblock_nxt(int);
  bool operator<(const ElementAccount &);
  bool operator>(const ElementAccount &);
  bool operator==(const ElementAccount &);
};
namespace RubbishAccount{
bool Insert(Account);//该函数插入成功为1，失败为0。
bool Delete(Account);//该函数删除成功为1，失败为0。
Account Find(Account);//这个函数会返回一个Account，如果没找到，返回一个空的账号。
}
#endif