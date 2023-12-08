#include "Book.hpp"
#include "Store.hpp"
#include "Check.hpp"
#include <bits/stdc++.h>
#include <cstring>

extern std::vector<Book> selected;

Book::Book() {
  strcpy(ISBN, "");
  strcpy(name, "");
  strcpy(author, "");
  strcpy(keyword, "");
  price = 0;
  quantity = 0;
}


void Book::SetISBN(char *txt) {
  CheckSize20(txt);
  CheckVisible(txt);
  strcpy(ISBN, txt);
  return; 
}

void Book::Copy(KeyBook &b) {
  strcpy(b.ISBN, ISBN);
  strcpy(b.name, name);
  strcpy(b.author, author);
  strcpy(b.keyword, keyword);
}

bool Book::operator>(const Book &b) const {
  return strcmp(ISBN, b.ISBN) > 0;
}

bool Book::operator<(const Book &b) const {
  return strcmp(ISBN, b.ISBN) < 0;
}

bool Book::operator==(const Book &b) const {
  return strcmp(ISBN, b.ISBN) == 0;
}

bool KeyBook::operator>(const KeyBook &b) const {
  if(strcmp(key, b.keyword) == 0) {
    return strcmp(ISBN, b.ISBN) > 0;
  }
  return strcmp(key, b.keyword) > 0;
}

bool KeyBook::operator<(const KeyBook &b) const {
  if(strcmp(key, b.keyword) == 0) {
    return strcmp(ISBN, b.ISBN) < 0;
  }
  return strcmp(key, b.keyword) < 0;
}

bool KeyBook::operator==(const KeyBook &b) const {
  return strcmp(key, b.keyword) == 0;
}

KeyBook::KeyBook():Book(){
  strcpy(key, "");
}

Book an_empty_book;
KeyBook an_empty_keybook;

void NewBook(char * txt) {
  Book tmp;
  tmp.SetISBN(txt);
  if(!(book_main.Find(tmp) == an_empty_book)) {
    throw(0);
  }
  book_main.Insert(tmp);//添加入主库。
  KeyBook tmp1;
  tmp1.SetISBN(txt);
  book_author.Insert(tmp1);//添加入作者库。
  book_keyword.Insert(tmp1);//添加入关键词库。
  book_name.Insert(tmp1);//添加入书名库。
  return;
}

void Book::Show() {
  cout << ISBN;
  cout <<'\t';
  cout << name;
  cout <<'\t';
  cout << author;
  cout <<'\t';
  cout << keyword;
  cout <<'\t';
  cout << std::fixed << std::setprecision(2) << price;//设置价格精度。
  cout <<'\t';
  cout << quantity;
  cout <<'\n';
  return;
}

void Select(char *txt) {
  Book tmp;
  tmp.SetISBN(txt);
  if(book_main.Find(tmp) == an_empty_book) {
    NewBook(txt);//主库未找到数据。新增一本书。 
  } else {
    tmp = book_main.Find(tmp);
    selected.pop_back();
    selected.push_back(tmp);
  }
  return;
}

void Showall() {
  book_main.PrintAll();
  return;
}
void ShowISBN(char *isbn) {
  Book tmp;
  tmp.SetISBN(isbn);
  tmp = book_main.Find(tmp);
  if(tmp == an_empty_book) {
    throw(0);
  }
  tmp.Show();
  return;
}

void Processshow(string txt) {
  if(txt.size() < 6) {
    throw(0);
  }//txt长度至少为6.
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
    txt.erase(0, 5);
    ShowISBN(const_cast<char *>(txt.c_str()));
    return;
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
    txt.erase(0, 6);
    ShowName(const_cast<char *>(txt.c_str()));
    return;
  }
  if(txt.size() < 8) {
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
    txt.erase(0, 8);
    ShowAuthor(const_cast<char *>(txt.c_str()));
    return;
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
    txt.erase(0, 9);
  }
}