#include <bits/stdc++.h>
#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP
template <class T>
class Check {
private:
  T element;
  bool flag;
public:
  Check<T> operator()(T);
  Check<T> toBe(T);
  Check<T> le(T);
  Check<T> ge(T);
  Check<T> Not();
  Check<T> Or();
  Check<T> And();
  Check<T> consistedOf(T);
  Check<T> toMatch(T);
  Check<T> toBeOneOf(T ...);
  template<class U>
  Check<T> toBe();

};
#endif