#include<bits/stdc++.h>
#ifndef BOOKDATA_HPP
#define BOOKDATA_HPP
class Book {
  protected:
    char ISBN[21];
    char name[61];
    char author[61];
    char keyword[61];
    int block_nxt;
    double price;
    double in_price;
  public:
  void Print();
  void Initial();
};
#endif