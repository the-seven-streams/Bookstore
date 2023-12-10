#include <bits/stdc++.h>
#ifndef BOOK_HPP
#define BOOK_HPP
#include "Store.hpp"
class Book;
class KeyBook;
extern Store<Book> book_main;
extern Store<KeyBook> book_author;
extern Store<KeyBook> book_name;
extern Store<KeyBook> book_keyword;
class Book {
protected:
  char ISBN[21];
  char name[61];
  char author[61];
  char keyword[61];
  double price;
  long long quantity;

public:
  Book();
  void SetName(char *); // 该函数用于设置书名。输入值即为书名。
  char *GetISBN();      // 该函数用于获取ISBN。
  void SetISBN(char *); // 该函数用于设置ISBN。输入值即为ISBN。
  void ModifyProcess(
      string); // 该函数用于修改书籍信息。输入内容为modify后的所有内容。
  void Import(int);     // 该函数用于进货。输入为进货数量。
  void Copy(KeyBook &); // 该函数用于将Book中的信息赋给KeyBook。
  void Show();          // 该函数用于打印书籍信息。
  void SetAuthor(char *); // 该函数用于设置作者。输入值即为作者。
  void SetKeyword(
      char *); // 该函数用于设置关键词。输入值即为关键词。（=后的内容，除引号）
  friend void Update(Book, Book); // 该函数用于将主库中的图书信息更新到其他库中。
  // 第一个参数为旧信息，第二个参数为新信息。
  friend double
  Buy(char *,
      int); // 该函数用于购买图书。第一个参数为ISBN，第二个参数为购买数量。
  virtual bool operator>(const Book &) const;
  virtual bool operator<(const Book &) const;
  virtual bool
  operator==(const Book &) const; // 书籍之间的大小关系定义为ISBN的字典序。
};

class KeyBook : public Book {
protected:
  char key[61]; // 该变量用于存储键值。
public:
  friend class Store<KeyBook>;
  KeyBook();
  bool operator>(const KeyBook &) const;
  bool operator<(const KeyBook &) const;
  bool operator==(const KeyBook &)
      const; // 书籍之间的大小关系由键值决定。如果键值相同，则比较ISBN。
  void SetKey(char *); // 设置键值。
};
void Select(char *);     // 该函数用于选择图书。输入值为ISBN。
void Showall();          // 该函数用于打印所有图书信息。
void ShowAuthor(char *); // 该函数用于打印指定作者的所有图书信息。输入值为作者。
void ShowName(char *); // 该函数用于打印指定书名的所有图书信息。输入值为书名。
void ShowKeyword(
    char *); // 该函数用于打印指定关键词的所有图书信息。输入值为关键词。
void ShowISBN(char *); // 该函数用于打印指定ISBN的图书信息。输入值为ISBN。
void Processshow(string); // 该函数用于处理show命令。输入值为show后的所有内容。
#endif