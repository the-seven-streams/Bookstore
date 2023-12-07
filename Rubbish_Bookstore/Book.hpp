#include<bits/stdc++.h>
#include"Store.hpp"
#ifndef BOOKDATA_HPP
#define BOOKDATA_HPP
class Book {
protected:
  char ISBN[21];
  char name[61];
  char author[61];
  char keyword[61];
  double price;
  int quantity;
public:
  Book();
  void NewBook(char *);
  void Modify(char *);
  void Import(char *);
  void Show();
};
#endif