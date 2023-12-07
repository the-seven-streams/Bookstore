#include <bits/stdc++.h>
#include "Book.hpp"
#ifndef BOOKISBN_HPP
#define BOOKISBN_HPP
using std::string;
using std::fstream;



class BookISBN: public Book{
public:
  bool operator<(const BookISBN &) const;
  bool operator>(const BookISBN &) const;
  bool operator==(const BookISBN &) const;
};

#endif