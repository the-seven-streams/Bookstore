#include "Check.hpp"

void CheckN(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      throw(0);
    }
  }
  return;
}

void CheckNLU(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      if (str[i] < 'a' || str[i] > 'z') {
        if (str[i] < 'A' || str[i] > 'Z') {
          if (str[i] != '_') {
            throw(0);
          }
        }
      }
    }
  }
  return;
}

void CheckEmpty(std::string txt) {
  if(!txt.empty()) {
    throw(0);
  }
  return;
}

void CheckSize30(char *str) {
  if(strlen(str) > 30) {
    throw(0);
  }
  return;
}

void CheckSize60(char *str) {
  if(strlen(str) > 60) {
    throw(0);
  }
  return;
}

void CheckSize20(char *str) {
  if(strlen(str) > 20) {
    throw(0);
  }
  return;
}

void CheckVisible(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] < 32 || str[i] > 126) {
      throw(0);
    }
  }
  return;
}

void CheckVisibleNoQuotation(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] < 32 || str[i] > 126) {
      if(str[i] == '\"') {
        throw(0);
      }
    }
  }
  return;
}

void CheckReal(char * str) {
  int len = strlen(str);
  int dot = 0;
  for (int i = 0; i < len; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      if(str[i] == '.') {
        ++dot;
        if(dot > 1) {
          throw(0);
        }
      } else {
        throw(0);
      }
    }
  }
  return;
}