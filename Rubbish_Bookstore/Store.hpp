#include<bits/stdc++.h>
#ifndef STORE_HPP
#define STORE_HPP
template<class T>
class Element {//这一部分不需要在意。存储所需。
private:
  int size;        
  int block_place; 
  int block_nxt;  

public:
  T element;
  Element() {
    size = 0;
    block_place = 0;
    block_nxt = 0;
  }
  void Setsize(int);
  int Getsize();
  int Getplace();
  void Setplace(int);
  int Getblock_nxt();
  void Setblock_nxt(int);
  bool operator<(const T &) const;
  bool operator>(const T &) const;
  bool operator==(const T &) const;
};
#endif