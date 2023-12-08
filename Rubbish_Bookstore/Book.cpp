#include "Book.hpp"
#include "Store.hpp"
#include "Check.hpp"
#include <bits/stdc++.h>
#include <cstring>

Book::Book() {
  strcpy(ISBN, "");
  strcpy(name, "");
  strcpy(author, "");
  strcpy(keyword, "");
  price = 0;
  quantity = 0;
}


void Book::SetISBN(char *txt) {
  CheckSize20(txt);
  CheckVisible(txt);
  strcpy(ISBN, txt);
  return; 
}

void Book::Copy(KeyBook &b) {
  strcpy(b.ISBN, ISBN);
  strcpy(b.name, name);
  strcpy(b.author, author);
  strcpy(b.keyword, keyword);
}

bool Book::operator>(const Book &b) const {
  return strcmp(ISBN, b.ISBN) > 0;
}

bool Book::operator<(const Book &b) const {
  return strcmp(ISBN, b.ISBN) < 0;
}

bool Book::operator==(const Book &b) const {
  return strcmp(ISBN, b.ISBN) == 0;
}

bool KeyBook::operator>(const KeyBook &b) const {
  if(strcmp(key, b.keyword) == 0) {
    return strcmp(ISBN, b.ISBN) > 0;
  }
  return strcmp(key, b.keyword) > 0;
}

bool KeyBook::operator<(const KeyBook &b) const {
  if(strcmp(key, b.keyword) == 0) {
    return strcmp(ISBN, b.ISBN) < 0;
  }
  return strcmp(key, b.keyword) < 0;
}

bool KeyBook::operator==(const KeyBook &b) const {
  return strcmp(key, b.keyword) == 0;
}

KeyBook::KeyBook():Book(){
  strcpy(key, "");
}

Book an_empty_book;
KeyBook an_empty_keybook;

void NewBook(char * txt) {
  Book tmp;
  tmp.SetISBN(txt);
  if(!(book_main.Find(tmp) == an_empty_book)) {
    throw(0);
  }
  book_main.Insert(tmp);//添加入主库。
  KeyBook tmp1;
  tmp1.SetISBN(txt);
  book_author.Insert(tmp1);//添加入作者库。
  book_keyword.Insert(tmp1);//添加入关键词库。
  book_name.Insert(tmp1);//添加入书名库。
  return;
}

void Book::Show() {
  cout << ISBN;
  cout <<'\t';
  cout << name;
  cout <<'\t';
  cout << author;
  cout <<'\t';
  cout << keyword;
  cout <<'\t';
  cout << std::fixed << std::setprecision(2) << price;//设置价格精度。
  cout <<'\t';
  cout << quantity;
  cout <<'\n';
  return;
}