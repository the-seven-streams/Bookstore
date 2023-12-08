#include "Book.hpp"
#include "Store.hpp"
#include "Check.hpp"
#include <bits/stdc++.h>

Book::Book() = default;

void Book::SetISBN(char *txt) {
  CheckSize20(txt);
  CheckVisible(txt);
  strcpy(ISBN, txt);
  return; 
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

Book an_empty_book;
KeyBook an_empty_keybook;