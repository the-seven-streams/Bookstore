#include<bits/stdc++.h>
#ifndef BOOK_HPP
#define BOOK_HPP
#include"Store.hpp"
class Book;
class KeyBook;
extern Store<Book> book_main;
extern Store<KeyBook> book_author;
extern Store<KeyBook> book_name;
extern Store<KeyBook> book_keyword;
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
  void Modify(char *, int);
  void Import(char *);
  void Copy(KeyBook &);
  void Show();
  virtual bool operator>(const Book &) const;
  virtual bool operator<(const Book &) const;
  virtual bool operator==(const Book &) const;
};

class KeyBook : public Book { 
protected:
  char key[61];
public:
  KeyBook();
  bool operator>(const KeyBook &) const;
  bool operator<(const KeyBook &) const;
  bool operator==(const KeyBook &) const;
};
void Select(char *);
void Showall();
void ShowAuthor(char *);
void ShowName(char *);
void ShowKeyword(char *);
#endif