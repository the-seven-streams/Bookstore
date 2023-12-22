#include <bits/stdc++.h>
#include <cstdarg>
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
    return *this;
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
  Check<T> Not() { flag ^= 1; return *this;}
  Check<T> Or() { return *this; }
  Check<T> And() { return *this; }
  Check<T> But() { return *this; }
  Check<T> consistedOf(T tar) {
    if(!flag) {
      for(int i = 0; i < element.size(); i++) {
        if(tar.find(element[i]) == -1) {
          throw(0);
        }
      }
    } else {
      bool not_found = 0;
      for(int i = 0; i < element.size(); i++) {
        if(tar.find(element[i]) == -1) {
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
    if(!(std::regex_match(element, exp) ^ flag)) {
      throw(0);
    }
    return *this;
  }
  template<typename ... Args>
  Check<T> toBeOneOf(T arg, Args... args) {
    if(arg == element) {
      if(!flag) {
        return *this;
      } else {
        throw(0);
      }
    }
    toBeOneOf(args...);
    return *this;
  }
  Check<T> toBeOneOf() {
    if(flag) {
      return *this;
    } else {
      throw(0);
    }
  }
  template <class U> Check<T> toBe() {
    T *res = new T(element);
    static_assert(dynamic_cast<U*>(res));
    delete res;
    return *this;
  }
};
#endif