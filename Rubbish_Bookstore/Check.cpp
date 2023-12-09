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
    if (str[i] <= 32 || str[i] > 126) {
      throw(0);
    }
  }
  return;
}

void CheckVisibleNoQuotation(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; ++i) {
    if (str[i] <= 32 || str[i] > 126) {
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

void CheckModify(std::string txt) {
  if(txt.empty()) {
    throw(0);
  }
  bool isbn = 0;
  bool name = 0;
  bool author = 0;
  bool keyword = 0;
  bool price = 0;
  while(!txt.empty()) {
    std::string addtion = ProcessTxt(txt);
    if(addtion.empty()) {
      throw(0);
    }
    if(addtion[0] != '-') {
      throw(0);
    }
    addtion.erase(0, 1);
    if(addtion.empty()) {
      throw(0);
    }
     if(txt.size() < 6) {
    throw(0);
  }
  if(txt[0] == 'I') {
    if(txt[1] != 'S') {
      throw(0);
    }
    if(txt[2] != 'B') {
      throw(0);
    }
    if(txt[3] != 'N') {
      throw(0);
    }
    if(txt[4] != '=') {
      throw(0);
    }
    if(isbn) {
      throw(0);
    }
    isbn = 1;
    continue;
  }
  if(txt.length() < 7) {
    throw(0);
  }
  if(txt[0] == 'p') {
    if(txt[1] != 'r') {
      throw(0);
    }
    if(txt[2] != 'i') {
      throw(0);
    }
    if(txt[3] != 'c') {
      throw(0);
    }
    if(txt[4] != 'e') {
      throw(0);
    }
    if(txt[5] != '=') {
      throw(0);
    }
    if(price) {
      throw(0);
    }
    price = 1;
    continue;
  }
  if(txt[txt.size() - 1] != '\"') {
    throw(0);
  }
  txt.erase(txt.size() - 1, 1);//在剩下的所有指令中，最后一位必须是引号。
  if(txt.size() < 7) {
    throw(0);
  }
  if(txt[0] == 'n') {
    if(txt[1] != 'a') {
      throw(0);
    }
    if(txt[2] != 'm') {
      throw(0);
    }
    if(txt[3] != 'e') {
      throw(0);
    }
    if(txt[4] != '=') {
      throw(0);
    }
    if(txt[5] != '\"') {
      throw(0);
    }
    if(name) {
      throw(0);
    }
    name = 1;
    continue;
  }
  if(txt.size() < 9) {
    throw(0);
  }
  if(txt[0] == 'a') {
    if(txt[1] != 'u') {
      throw(0);
    }
    if(txt[2] != 't') {
      throw(0);
    }
    if(txt[3] != 'h') {
      throw(0);
    }
    if(txt[4] != 'o') {
      throw(0);
    }
    if(txt[5] != 'r') {
      throw(0);
    }
    if(txt[6] != '=') {
      throw(0);
    }
    if(txt[7] != '\"') {
      throw(0);
    }
    if(author) {
      throw(0);
    }
    author = 1;
    continue;
  }
  if(txt.size() < 10) {
    throw(0);
  }
  if(txt[0] == 'k') {
    if(txt[1] != 'e') {
      throw(0);
    }
    if(txt[2] != 'y') {
      throw(0);
    }
    if(txt[3] != 'w') {
      throw(0);
    }
    if(txt[4] != 'o') {
      throw(0);
    }
    if(txt[5] != 'r') {
      throw(0);
    }
    if(txt[6] != 'd') {
      throw(0);
    }
    if(txt[7] != '=') {
      throw(0);
    }
    if(txt[8] != '\"') {
      throw(0);
    }
    if(keyword) {
      throw(0);
    }
    keyword = 1;
    return;
  }
  throw(0);
  }
  return;
}