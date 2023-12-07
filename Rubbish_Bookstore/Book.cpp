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

