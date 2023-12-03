#include "BookISBN.hpp"
#include "Book.hpp"

bool operator<(const BookISBN& lhs, const BookISBN& rhs) {
  return strcmp(lhs.ISBN, rhs.ISBN) < 0;
}