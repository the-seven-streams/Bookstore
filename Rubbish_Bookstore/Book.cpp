#include "Book.hpp"
using std::cin;
void Book::Initial() {
  cin >> ISBN;
  cin >> name;
  cin >> author;
  cin >> keyword;
  cin >> in_price;
}