#include"Store.hpp"
bool Element::operator<(const Element &b) const{
  return user < b.user;
}
bool Element::operator>(const Element &b) const{
  return user > b.user;
}
bool Element::operator==(const Element &b) const{
  return user == b.user;
}
int Element::Getsize() { return size; }
void Element::Setsize(int x) {
  size = x;
  return;
}
int Element::Getplace() { return block_place; }
void Element::Setplace(int x) {
  block_place = x;
  return;
}
int Element::Getblock_nxt() { return block_nxt; }
void Element::Setblock_nxt(int x) {
  block_nxt = x;
  return;
}