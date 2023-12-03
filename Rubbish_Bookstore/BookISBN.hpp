#include <bits/stdc++.h>
#include "Book.hpp"
#ifndef BOOKISBN_HPP
#define BOOKISBN_HPP
using std::string;
using std::fstream;



class BookISBN: public Book{
public:
  friend bool operator<(const BookISBN& lhs, const BookISBN& rhs);
};

#endif