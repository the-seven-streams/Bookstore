#include <bits/stdc++.h>
#include <cstdio>
#include <initializer_list>
#include <regex>
#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP
template <class T> class Check {
private:
  T element;
  bool flag;

public:
  Check<T> operator()(T in) {
    element = in;
    flag = 0;
  }
  Check<T> toBe(T in) {
    if (!flag) {
      if (element != in) {
        throw(0);
      }
    } else {
      if (element == in) {
        throw(0);
      }
    }
    return *this;
  }
  Check<T> le(T in) {
    if (!flag) {
      if (element > in) {
        throw(0);
      }
    } else {
      if (element <= in) {
        throw(0);
      }
    }
    return *this;
  }
  Check<T> ge(T in) {
    if (!flag) {
      if (element < in) {
        throw(0);
      }
    } else {
      if (element >= in) {
        throw(0);
      }
    }
    return *this;
  }
  Check<T> Not() { flag ^= 1; }
  Check<T> Or() { return *this; }
  Check<T> And() { return *this; }
  Check<T> But() { return *this; }
  Check<T> consistedOf(T tar) {
    if(!flag) {
      for(int i = 0; i < tar.size(); i++) {
        if(element.find(tar[i]) == -1) {
          throw(0);
        }
      }
    } else {
      bool not_found = 0;
      for(int i = 0; i < tar.size(); i++) {
        if(element.find(tar[i]) == -1) {
          not_found = 1;
          break;
        }
      }
      if(!not_found) {
        throw(0);
      }
    }
    return *this; 
  }
  Check<T> toMatch(T tar) {
    std::regex exp(tar);
    if(!(std::regex_match(exp, element) ^ flag)) {
      throw(0);
    }
    return *this;
  }
  Check<T> toBeOneOf(std::initializer_list<T> total) {
    bool found = 0;
    for(int i = 0; i < total.size(); i++) {
      if(total[i] == element) {
        found = 1;
        break;
      }
    }
    if(!(found ^ flag)) {
      throw(0);
    }
    return *this;
  }
  template <class U> Check<T> toBe() {
    static_assert(dynamic_cast<U>(element));
    return *this;
  }
};
#endif