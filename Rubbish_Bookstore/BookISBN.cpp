#include "BookISBN.hpp"
#include "Book.hpp"

bool BookISBN::operator<(const BookISBN &b) const {
  return ISBN < b.ISBN;
}
bool BookISBN::operator>(const BookISBN &b) const {
  return ISBN > b.ISBN;
}
bool BookISBN::operator==(const BookISBN &b) const {
  return ISBN == b.ISBN;
}