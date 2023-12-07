#include<bits/stdc++.h>
#include"Store.hpp"
#ifndef BOOKDATA_HPP
#define BOOKDATA_HPP
class Book;
extern Store<Book> book_main;

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
  void SetISBN(char *);
  void Modify(char *);
  void Import(char *);
  void Show();
  virtual bool operator>(const Book &) const;
  virtual bool operator<(const Book &) const;
  virtual bool operator==(const Book &) const;
};
void NewBook(char *);
#endif