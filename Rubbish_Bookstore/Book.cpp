#include "Book.hpp"
#include "Store.hpp"
#include "Check.hpp"
#include <bits/stdc++.h>
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
  if(strcmp(key, b.key) == 0) {
    return strcmp(ISBN, b.ISBN) > 0;
  }
  return strcmp(key, b.key) > 0;
}

bool KeyBook::operator<(const KeyBook &b) const {
  if(strcmp(key, b.key) == 0) {
    return strcmp(ISBN, b.ISBN) < 0;
  }
  return strcmp(key, b.key) < 0;
}

bool KeyBook::operator==(const KeyBook &b) const {
  return strcmp(key, b.key) == 0 && strcmp(ISBN, b.ISBN) == 0;
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
  if(tmp == an_empty_book) {
    cout << '\n';
    return;
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
    ShowKeyword(const_cast<char *>(txt.c_str()));
    return;
  }
  throw(0);
}

char* Book::GetISBN() {
  return ISBN;
}

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
  KeyBook tmp;
  tmp.SetKey(keyword);
  book_keyword.FindAll(tmp);
  return;
}

void Book::ModifyProcess(string txt) {//传入内容不应该有减号。
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
    txt.erase(0, 5);
    Book tmp;
    tmp.SetISBN(const_cast<char *>(txt.c_str()));
    if(!(book_main.Find(tmp) == an_empty_book)) {
      throw(0);
    }//主库中已经有了这个ISBN。
    ModifyISBN(const_cast<char *>(txt.c_str()));
    return;
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
    txt.erase(0, 6);
    ModifyPrice(const_cast<char *>(txt.c_str()));
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
    ModifyName(const_cast<char *>(txt.c_str()));
    return;
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
    txt.erase(0, 8);
    ModifyAuthor(const_cast<char *>(txt.c_str()));
    return;
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
    txt.erase(0, 9);
    CheckRepeat(txt);
    ModifyKeyword(const_cast<char *>(txt.c_str()));
    return;
  }
  throw(0);
}

void Book::ModifyISBN(char *txt) {
  CheckSize20(txt);
  CheckVisible(txt);
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.SetISBN(txt);
  //tmp是旧书籍，tmp1是新书籍。
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  for(auto it = selected.begin(); it != selected.end(); it++) {
    if(*it == tmp) {
      *it = tmp1;
    }
  }//更新selected中的数据。
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
  if(keyword_total.empty()) {
    tmp.SetKey(tmp.keyword);
    book_keyword.Delete(tmp);
  }
  while(!keyword_total.empty()) {
    string tmp_keyword = ProcessKey(keyword_total);
    tmp.SetKey(const_cast<char *>(tmp_keyword.c_str()));
    book_keyword.Delete(tmp);
  }
  //删除旧书。
  newbook.Copy(tmp);
  tmp.SetKey(tmp.author);
  book_author.Insert(tmp);
  tmp.SetKey(tmp.name);
  book_name.Insert(tmp);
  keyword_total = tmp.keyword;
  if(keyword_total.empty()) {
    tmp.SetKey(tmp.keyword);
    book_keyword.Insert(tmp);
  }
  while(!keyword_total.empty()) {
    string tmp_keyword = ProcessKey(keyword_total);
    tmp.SetKey(const_cast<char *>(tmp_keyword.c_str()));
    book_keyword.Insert(tmp);
  }
  //插入新书。
  return;
}

void Book::SetName(char *txt) {
  strcpy(name, txt);
  return;
}


void Book::ModifyName(char *txt) {
  CheckSize60(txt);
  CheckVisibleNoQuotation(txt);
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.SetName(txt);
  //tmp是旧书籍，tmp1是新书籍。
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  return;
}

void Book::SetAuthor(char *txt) {
  strcpy(author, txt);
  return;
}

void Book::ModifyAuthor(char *txt) {
  CheckSize60(txt);
  CheckVisibleNoQuotation(txt);
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.SetAuthor(txt);
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  return;
}

void Book::SetKeyword(char *txt) {
  strcpy(keyword, txt);
  return;
}

void Book::ModifyKeyword(char *txt) {
  CheckSize60(txt);
  CheckVisibleNoQuotation(txt);
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.SetKeyword(txt);
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
  return;
}

void Book::ModifyPrice(char *txt) {
  CheckReal(txt);
  Book tmp, tmp1;
  tmp = book_main.Find(*this);
  tmp1 = tmp;
  tmp1.price = atof(txt);
  book_main.Delete(tmp);
  book_main.Insert(tmp1);
  Update(tmp, tmp1);
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

void Buy(char *txt, int number) {
  CheckSize20(txt);
  CheckVisible(txt);
  Book tmp;
  tmp.SetISBN(txt);
  tmp = book_main.Find(tmp);
  if(tmp == an_empty_book) {
    throw(0);
  }
  if(tmp.quantity < number) {
    throw(0);
  }
  tmp.quantity -= number;
  total_income += tmp.price * number;
  cout << std::fixed << std::setprecision(2) << tmp.price * number << '\n';
  book_main.Delete(tmp);
  book_main.Insert(tmp);
  Update(tmp, tmp);
  return;
}