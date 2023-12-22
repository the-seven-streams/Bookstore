#include "Check.hpp"
#include "Book.hpp"
#include <cstring>
#include <regex>
extern std::vector<Book> selected;
void CheckN(char *str) {
  int len = strlen(str);
  if (len == 0) {
    throw(0);
  }
  for (int i = 0; i < len; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      throw(0);
    }
  }
  if (len == 10) {
    long long sum = 0;
    for (int i = 0; i < 10; ++i) {
      sum *= 10;
      sum += (str[i] - '0');
    }
    if (sum > 2147483647) {
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
  if (!txt.empty()) {
    throw(0);
  }
  return;
}

void CheckSize30(char *str) {
  if (strlen(str) > 30) {
    throw(0);
  }
  return;
}

void CheckSize60(char *str) {
  if (strlen(str) > 60) {
    throw(0);
  }
  return;
}

void CheckSize20(char *str) {
  if (strlen(str) > 20) {
    throw(0);
  }
  return;
}

void CheckSize10(char *str) {
  if (strlen(str) > 10) {
    throw(0);
  }
  return;
}
void CheckVisible(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] <= 32 || str[i] > 126) {
      throw(0);
    }
  }
  return;
}

void CheckVisibleNoQuotation(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] < '!' || str[i] > '~') {
      throw(0);
    }
  }
  for (int i = 0; i < len; ++i) {
    if (str[i] == '\"') {
      throw(0);
    }
  }
  return;
}

void CheckVisibleNoQuotationOrHan(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] < '!' || str[i] > '~') {
      int trans = static_cast<int>(str[i]);
      if (trans >= 0x4E00 && trans <= 0x9FFF) {
        continue;
      }
      if (trans >= 0x3400 && trans <= 0x4DBF) {
        continue;
      }
      if (trans >= 0x20000 && trans <= 0x2A6DF) {
        continue;
      }
      if (trans >= 0x2A700 && trans <= 0x2B73F) {
        continue;
      }
      if(trans >=0x2B740 && trans <= 0x2B81F) {
        continue;
      }
      if(trans >=0x2B820 && trans <= 0x2CEAF) {
        continue;
      }
      if(trans>=0x2CEB0 && trans<=0x2EBEF) {
        continue;
      }
      if(trans>=0x30000 && trans<=0x3134F) {
        continue;
      }
      if(trans>=0x31350 && trans<= 0x323AF) {
        continue;
      }
      if(trans>=0xF900 && trans<=0xFAFF) {
        continue;
      }
      if(trans>=0x2F800 && trans<=0x2FA1F) {
        continue;
      }
      throw(0);
    }
  }
  for (int i = 0; i < len; ++i) {
    if (str[i] == '\"') {
      throw(0);
    }
  }
  return;
}

void CheckReal(char *str) {
  int len = strlen(str);
  int dot = 0;
  if (len == 0) {
    throw(0);
  }
  for (int i = 0; i < len; ++i) {
    if (str[i] < '0' || str[i] > '9') {
      if (str[i] == '.') {
        ++dot;
        if (dot > 1) {
          throw(0);
        }
      } else {
        throw(0);
      }
    }
  }
  return;
}

void CheckRepeat(std::string txt1) {
  std::string txt = txt1;
  std::set<std::string> s;
  while (!txt.empty()) {
    std::string word = ProcessKey(txt);
    if (word.empty()) {
      throw(0);
    }
    if (s.find(word) != s.end()) {
      throw(0);
    }
    s.insert(word);
  }
  return;
}

void CheckSize13(char *str) {
  if (strlen(str) > 13) {
    throw(0);
  }
  return;
}