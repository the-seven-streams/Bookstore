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
  int total = 0;
  for (int i = 0; i < len; i++, total++) {
    if (str[i] < '!' || str[i] > '~') {
      long long byte1 = static_cast<unsigned char>(str[i]);
      long long trans = byte1;
      int how_many = 0;
      for (int i = 8; i; i--) {
        if (byte1 & (1 << (i - 1))) {
          how_many++;
        } else {
          break;
        }
      }
      if (how_many == 0) {
        how_many = 1;
        trans = byte1;
      }
      if (how_many == 2) {
        if (i + 1 >= len) {
          throw(0);
        }
        long long byte2 = static_cast<unsigned char>(str[i + 1]);
        trans -= 192;
        trans <<= 6;
        trans += byte2;
        trans -= 128;
      }
      if (how_many == 3) {
        if (i + 2 >= len) {
          throw(0);
        }
        long long byte2 = static_cast<unsigned char>(str[i + 1]);
        trans -= 224;
        trans <<= 6;
        trans += byte2;
        trans -= 128;
        trans <<= 6;
        long long byte3 = static_cast<unsigned char>(str[i + 2]);
        trans -= 128;
        trans += byte3;
      }
      if (how_many == 4) {
        if (i + 3 >= len) {
          throw(0);
        }
        long long byte2 = static_cast<unsigned char>(str[i + 1]);
        trans -= 240;
        trans <<= 6;
        trans += byte2;
        trans -= 128;
        trans <<= 6;
        long long byte3 = static_cast<unsigned char>(str[i + 2]);
        trans -= 128;
        trans <<= 6;
        long long byte4 = static_cast<unsigned char>(str[i + 3]);
        trans += byte4;
        trans -= 128;
      }
      if(trans == 0x0087 || trans == 0x2014 || trans == 0xFF08 || trans == 0xFF09 ||
      trans == 0xFF1A) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x4E00 && trans <= 0x9FFF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x3400 && trans <= 0x4DBF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x20000 && trans <= 0x2A6DF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x2A700 && trans <= 0x2B73F) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x2B740 && trans <= 0x2B81F) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x2B820 && trans <= 0x2CEAF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x2CEB0 && trans <= 0x2EBEF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x30000 && trans <= 0x3134F) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x31350 && trans <= 0x323AF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0xF900 && trans <= 0xFAFF) {
        i += (how_many - 1);
        continue;
      }
      if (trans >= 0x2F800 && trans <= 0x2FA1F) {
        i += (how_many - 1);
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
  if(total > 60) {
    throw(0);
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