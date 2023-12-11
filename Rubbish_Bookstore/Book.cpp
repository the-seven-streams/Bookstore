#include "Book.hpp"
#include "Check.hpp"
#include "Store.hpp"
#include <bits/stdc++.h>
#include <cmath>
#include <cstring>

extern std::vector<Book> selected;
extern double total_income;

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
  b.price = price;
  b.quantity = quantity;
  return;
}

bool Book::operator>(const Book &b) const { return strcmp(ISBN, b.ISBN) > 0; }

bool Book::operator<(const Book &b) const { return strcmp(ISBN, b.ISBN) < 0; }

bool Book::operator==(const Book &b) const { return strcmp(ISBN, b.ISBN) == 0; }

bool KeyBook::operator>(const KeyBook &b) const {
  if (strcmp(key, b.key) == 0) {
    return strcmp(ISBN, b.ISBN) > 0;
  }
  return strcmp(key, b.key) > 0;
}

bool KeyBook::operator<(const KeyBook &b) const {
  if (strcmp(key, b.key) == 0) {
    return strcmp(ISBN, b.ISBN) < 0;
  }
  return strcmp(key, b.key) < 0;
}

bool KeyBook::operator==(const KeyBook &b) const {
  return strcmp(key, b.key) == 0 && strcmp(ISBN, b.ISBN) == 0;
}

KeyBook::KeyBook() : Book() { strcpy(key, ""); }

Book an_empty_book;
KeyBook an_empty_keybook;

void NewBook(char *txt) {
  Book tmp;
  tmp.SetISBN(txt);
  book_main.Insert(tmp); // 添加入主库。
  KeyBook tmp1;
  tmp1.SetISBN(txt);
  book_author.Insert(tmp1);  // 添加入作者库。
  book_keyword.Insert(tmp1); // 添加入关键词库。
  book_name.Insert(tmp1);    // 添加入书名库。
  return;
}

void Book::Show() {
  cout << ISBN;
  cout << '\t';
  cout << name;
  cout << '\t';
  cout << author;
  cout << '\t';
  cout << keyword;
  cout << '\t';
  cout << std::fixed << std::setprecision(2) << price + 0.00000000001; // 设置价格精度。
  cout << '\t';
  cout << quantity;
  cout << '\n';
  return;
}

void Select(char *txt) {
  Book tmp;
  tmp.SetISBN(txt);
  if (book_main.Find(tmp) == an_empty_book) {
    NewBook(txt); // 主库未找到数据。新增一本书。
  } else {
    tmp = book_main.Find(tmp);
  }
  selected.pop_back();
  selected.push_back(tmp);
  return;
}

void Showall() {
  book_main.PrintAll();
  return;
}
void ShowISBN(char *isbn) {
  CheckSize20(isbn);
  CheckVisible(isbn);
  Book tmp;
  tmp.SetISBN(isbn);
  tmp = book_main.Find(tmp);
  if (tmp == an_empty_book) {
    cout << '\n';
    return;
  }
  tmp.Show();
  return;
}

void Processshow(string txt) {
  if (txt.size() < 6) {
    throw(0);
  } // txt长度至少为6.
  if (txt[0] == 'I') {
    string res;
    res = txt.substr(0, 5);
    if (res != "ISBN=") {
      throw(0);
    }
    txt.erase(0, 5);
    ShowISBN(const_cast<char *>(txt.c_str()));
    return;
  }
  if (txt[txt.size() - 1] != '\"') {
    throw(0);
  }
  txt.erase(txt.size() - 1, 1); // 在剩下的所有指令中，最后一位必须是引号。
  if (txt.size() < 7) {
    throw(0);
  }
  if (txt[0] == 'n') {
    string res;
    res = txt.substr(0, 6);
    if (res != "name=\"") {
      throw(0);
    }
    txt.erase(0, 6);
    ShowName(const_cast<char *>(txt.c_str()));
    return;
  }
  if (txt.size() < 9) {
    throw(0);
  }
  if (txt[0] == 'a') {
    string res;
    res = txt.substr(0, 8);
    if (res != "author=\"") {
      throw(0);
    }
    txt.erase(0, 8);
    ShowAuthor(const_cast<char *>(txt.c_str()));
    return;
  }
  if (txt.size() < 10) {
    throw(0);
  }
  if (txt[0] == 'k') {
    string res;
    res = txt.substr(0, 9);
    if (res != "keyword=\"") {
      throw(0);
    }
    txt.erase(0, 9);
    ShowKeyword(const_cast<char *>(txt.c_str()));
    return;
  }
  throw(0);
}

char *Book::GetISBN() { return ISBN; }

void KeyBook::SetKey(char *txt) {
  strcpy(key, txt);
  return;
}

void ShowAuthor(char *author) {
  CheckSize60(author);
  CheckVisibleNoQuotation(author);
  KeyBook tmp;
  tmp.SetKey(author);
  book_author.FindAll(tmp);
  return;
}

void ShowName(char *name) {
  CheckSize60(name);
  CheckVisibleNoQuotation(name);
  KeyBook tmp;
  tmp.SetKey(name);
  book_name.FindAll(tmp);
  return;
}

void ShowKeyword(char *keyword) {
  CheckSize60(keyword);
  CheckVisibleNoQuotation(keyword);
  for (int i = 0; i < strlen(keyword); ++i) {
    if (keyword[i] == '|') {
      throw(0);
    }
  }
  KeyBook tmp;
  tmp.SetKey(keyword);
  book_keyword.FindAll(tmp);
  return;
}

void Book::ModifyProcess(string txt) {
  Book tmp1 = an_empty_book;
  Book tmp;
  string name_txt;
  string author_txt;
  string keyword_txt;
  double price_num;
  string ISBN_txt;
  bool name = 0;
  bool author = 0;
  bool ISBN = 0;
  bool key = 0;
  bool price = 0;
  while (!txt.empty()) {
    string addtion = ProcessTxt(txt);
    if (addtion == "") {
      throw(0);
    }
    if (addtion.size() < 7) {
      throw(0);
    }
    if (!(addtion[0] == '-')) {
      throw(0);
    }
    addtion.erase(0, 1);
    if (addtion[0] == 'I') {
      string res1;
      res1 = addtion.substr(0, 5);
      if (res1 != "ISBN=") {
        throw(0);
      }
      addtion.erase(0, 5);
      if (ISBN) {
        throw(0);
      }
      ISBN = 1;
      CheckSize20(const_cast<char *>(addtion.c_str()));
      CheckVisible(const_cast<char *>(addtion.c_str()));
      ISBN_txt = addtion;
      if (ISBN_txt == tmp1.GetISBN()) {
        throw(0);
      }
      continue;
    }
    if (addtion[0] == 'p') {
      string res;
      res = addtion.substr(0, 6);
      if (res != "price=") {
        throw(0);
      }
      addtion.erase(0, 6);
      if (price) {
        throw(0);
      }
      price = 1;
      CheckReal(const_cast<char *>(addtion.c_str()));
      CheckSize13(const_cast<char *>(addtion.c_str()));
      price_num = atof(const_cast<char *>(addtion.c_str()));
      continue;
    }
    if (addtion.size() < 8) {
      throw(0);
    }
    if (addtion[addtion.size() - 1] != '\"') {
      throw(0);
    }
    addtion.erase(addtion.size() - 1,
                  1); // 在剩下的所有指令中，最后一位必须是引号。
    if (addtion[0] == 'n') {
      string res = addtion.substr(0, 6);
      if (res != "name=\"") {
        throw(0);
      }
      addtion.erase(0, 6);
      if (name) {
        throw(0);
      }
      name = 1;
      CheckSize60(const_cast<char *>(addtion.c_str()));
      CheckVisibleNoQuotation(const_cast<char *>(addtion.c_str()));
      name_txt = addtion;
      continue;
    }
    if (addtion.size() < 9) {
      throw(0);
    }
    if (addtion[0] == 'a') {
      string res = addtion.substr(0, 8);
      if (res != "author=\"") {
        throw(0);
      }
      addtion.erase(0, 8);
      if (author) {
        throw(0);
      }
      author = 1;
      CheckSize60(const_cast<char *>(addtion.c_str()));
      CheckVisibleNoQuotation(const_cast<char *>(addtion.c_str()));
      author_txt = addtion;
      continue;
    }
    if (addtion.size() < 10) {
      throw(0);
    }
    if (addtion[0] == 'k') {
      string res = addtion.substr(0, 9);
      if (res != "keyword=\"") {
        throw(0);
      }
      addtion.erase(0, 9);
      if (key) {
        throw(0);
      }
      key = 1;
      CheckSize60(const_cast<char *>(addtion.c_str()));
      CheckRepeat(addtion);
      CheckVisibleNoQuotation(const_cast<char *>(addtion.c_str()));
      keyword_txt = addtion;
      continue;
    }
    throw(0);
  }
  if (!name && !author && !key && !price && !ISBN) {
    throw(0);
  }
  tmp = book_main.Find(*this); // 旧信息
  tmp1 = tmp;
  if (name) {
    tmp1.SetName(const_cast<char *>(name_txt.c_str()));
  }
  if (author) {
    tmp1.SetAuthor(const_cast<char *>(author_txt.c_str()));
  }
  if (key) {
    tmp1.SetKeyword(const_cast<char *>(keyword_txt.c_str()));
  }
  if (price) {
    tmp1.price = price_num;
  }
  if (ISBN) {
    tmp1.SetISBN(const_cast<char *>(ISBN_txt.c_str()));
    if (!(book_main.Find(tmp1) == an_empty_book)) {
      throw(0);
    } // 说明这个ISBN号已经被使用。
    for (auto it = selected.begin(); it != selected.end(); ++it) {
      if (*it == tmp) {
        *it = tmp1;
      }
    } // 修改原有信息。
  }
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  return;
}

void Update(Book old, Book newbook) {
  KeyBook tmp;
  old.Copy(tmp);
  tmp.SetKey(tmp.author);
  book_author.Delete(tmp);
  tmp.SetKey(tmp.name);
  book_name.Delete(tmp);
  string keyword_total = tmp.keyword;
  if (keyword_total.empty()) {
    tmp.SetKey(tmp.keyword);
    book_keyword.Delete(tmp);
  }
  while (!keyword_total.empty()) {
    string tmp_keyword = ProcessKey(keyword_total);
    tmp.SetKey(const_cast<char *>(tmp_keyword.c_str()));
    book_keyword.Delete(tmp);
  }
  // 删除旧书。
  newbook.Copy(tmp);
  tmp.SetKey(tmp.author);
  book_author.Insert(tmp);
  tmp.SetKey(tmp.name);
  book_name.Insert(tmp);
  keyword_total = tmp.keyword;
  if (keyword_total.empty()) {
    tmp.SetKey(tmp.keyword);
    book_keyword.Insert(tmp);
  }
  while (!keyword_total.empty()) {
    string tmp_keyword = ProcessKey(keyword_total);
    tmp.SetKey(const_cast<char *>(tmp_keyword.c_str()));
    book_keyword.Insert(tmp);
  }
  // 插入新书。
  return;
}

void Book::SetName(char *txt) {
  strcpy(name, txt);
  return;
}

void Book::SetAuthor(char *txt) {
  strcpy(author, txt);
  return;
}

void Book::SetKeyword(char *txt) {
  strcpy(keyword, txt);
  return;
}

void Book::Import(int num) {
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.quantity += num;
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  return;
}

double Buy(char *txt, int number) {
  CheckSize20(txt);
  CheckVisible(txt);
  Book tmp;
  tmp.SetISBN(txt);
  tmp = book_main.Find(tmp);
  if (tmp == an_empty_book) {
    throw(0);
  }
  if (tmp.quantity < number) {
    throw(0);
  }
  if (number <= 0) {
    throw(0);
  }
  tmp.quantity -= number;
  total_income += tmp.price * number;
  cout << std::fixed << std::setprecision(2) << tmp.price * number + 0.00000000001
  << '\n';
  book_main.Delete(tmp);
  book_main.Insert(tmp);
  Update(tmp, tmp);
  return tmp.price * number;
}