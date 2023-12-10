#include <algorithm>
#include <bits/stdc++.h>
#include "Book.hpp"
#ifndef STORE_HPP
#define STORE_HPP
using std::cout;
using std::fstream;
using std::string;
using std::upper_bound;
using std::lower_bound;
class Book;
class KeyBook;
template <class T> class Element {
private:
  int size;
  int block_place;
  int block_nxt;

public:
  T element;
  Element() {
    size = 0;
    block_place = 0;
    block_nxt = 0;
  }
  void Setsize(int x) {
    size = x;
    return;
  }
  int Getsize() { return size; }
  int Getplace() { return block_place; }
  void Setplace(int x) {
    block_place = x;
    return;
  }
  int Getblock_nxt() { return block_nxt; }
  void Setblock_nxt(int x) {
    block_nxt = x;
    return;
  }
  bool operator<(const Element &a) const { return element < a.element; }
  bool operator>(const Element &a) const { return element > a.element; }
  bool operator==(const Element &a) const { return element == a.element; }
};

template <class W, int info_len = 2> class MemoryRiver {
private:
  fstream file;
  string file_name;
  int sizeofT = sizeof(W);

public:
  MemoryRiver() {}

  MemoryRiver(const string &file_name) : file_name(file_name) {
    initialise();
    return;
  }

  void initialise() {
    if (access(file_name.c_str(), F_OK) == 0) {
      return;
    }
    file.open(file_name, fstream::out);
    int tmp = 0;
    for (int i = 0; i < info_len; ++i)
      file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
  }

  // 读出第n个int的值赋给tmp，1_base
  void get_info(int &tmp, int n) {
    if (n > info_len)
      return;
    file.open(file_name);
    file.seekg((n - 1) * sizeof(int));
    file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
    return;
  }

  // 将tmp写入第n个int的位置，1_base
  void write_info(int tmp, int n) {
    if (n > info_len)
      return;
    file.open(file_name);
    file.seekp((n - 1) * sizeof(int), fstream::beg);
    file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
    return;
  }

  // 在文件合适位置写入类对象t，并返回写入的位置索引index
  // 位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  // 位置索引index可以取为对象写入的起始位置
  void write(W &t, long long place, int size = 1) {
    file.open(file_name);
    file.seekp(place);
    file.write(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
    return;
  }
  void read(W &t, const long long index, int size = 1) {
    file.open(file_name);
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
    return;
  }

}; // 第一个数据记录了索引块的总个数。
template <class T> class Store {
private:
  static const int largest = 500;
  static const int limit = 480;
  Element<T> res1[500], res2[500];
  MemoryRiver<Element<T>, 3> Data;
  int start = 0;
  int total = 0;
  int current = 0;

public:
  Store(string txt) : Data(txt) {
    Data.initialise();
    Data.get_info(total, 1);
    Data.get_info(start, 2);
    Data.get_info(current, 3);
    Data.read(res1[1], 12, total);
    return;
  }//这一部分既是在对文件本身进行初始化，同时也是在对内存进行初始化。

  Element<T> ArrayInsert(Element<T> &to_insert, int place, int size,
                         bool &flag) {
    Data.read(res2[1], place * largest * sizeof(Element<T>) + 12, size);
    // 读出原有数据块。
    int num = lower_bound(res2 + 1, res2 + size + 1, to_insert) - res2 -
              1; // 找到数据位置
    if ((num < size) && (res2[num + 1] == to_insert)) {
      flag = 1;
      return to_insert;
    }
    if (!num) {
      Data.write(to_insert, place * largest * sizeof(Element<T>) + 12);
      Data.write(res2[1],
                 place * largest * sizeof(Element<T>) + 12 + sizeof(Element<T>),
                 size);
      return to_insert;
    } // 说明写入的元素最小
    Data.write(res2[1], place * largest * sizeof(Element<T>) + 12, num);
    Data.write(to_insert, place * largest * sizeof(Element<T>) + 12 +
                              num * sizeof(Element<T>));
    if (size != num) {
      Data.write(res2[num + 1],
                 place * largest * sizeof(Element<T>) + 12 +
                     (num + 1) * sizeof(Element<T>),
                 size - num);
    }
    return res2[1];
  }//返回值，指示索引内容。


  bool ArrayFind(Element<T> &to_find, int place, int size, bool &found) {
    Data.read(res2[1], place * largest * sizeof(Element<T>) + 12, size);
    int num = lower_bound(res2 + 1, res2 + size + 1, to_find) - res2;
    if (num > size) {
      return 0;
    }
    if (res2[num] == to_find) {
      found = 1;
      to_find = res2[num];
      return 1;
    } else {
      return 0;
    }
  }

  bool ArrayDel(Element<T> &to_del, int place, int size) {
    Data.read(res2[1], place * largest * sizeof(Element<T>) + 12, size);
    int num = lower_bound(res2 + 1, res2 + size + 1, to_del) - res2 - 1;
    if (!(to_del == res2[num + 1])) {
      return 0; // 没有删除成功。
    }
    if (!num) {
      Data.write(res2[2], place * largest * sizeof(Element<T>) + 12, size - 1);
    } else {
      Data.write(res2[1], place * largest * sizeof(Element<T>) + 12, num);
      Data.write(res2[num + 2],
                 place * largest * sizeof(Element<T>) + 12 +
                     num * sizeof(Element<T>),
                 size - num - 1);
    }
    return 1;
  }

  int IndexFind(Element<T> &x) {
    int last = start;
    for (int i = start; i; i = res1[i].Getblock_nxt()) {
      if (x < res1[i]) {
        return last;
      }
      last = i;
    }
    return last;
  } // 这个函数的目的是找到目标块。

  void SplitBlock(int num, int size) {
    int mid = size / 2;
    Element<T> origin, new_block;
    origin = res1[num];
    Data.read(res2[1], origin.Getplace() * largest * sizeof(Element<T>) + 12,
              size); // 读入原有数据块。
    total++;
    current++;
    Data.write(res2[mid + 1], current * largest * sizeof(Element<T>) + 12,
               size - mid); // 写入新的数据块。
    new_block = res2[mid + 1];
    new_block.Setsize(size - mid);
    new_block.Setblock_nxt(origin.Getblock_nxt());
    new_block.Setplace(current);
    res1[total] = new_block;
    origin.Setsize(mid);
    origin.Setblock_nxt(total);
    res1[num] = origin;
    return;
  }

  bool Ins(Element<T> to_insert) {
    if (total == 0) {
      total++;
      to_insert.Setplace(1);
      to_insert.Setsize(1);
      start = 1;
      current = 1;
      res1[1] = to_insert;
      Data.write(to_insert, 12 + largest * sizeof(Element<T>), 1);
      return 0;
    } // 说明没有元素。
    Element<T> tmp, tmp2;
    int target = IndexFind(to_insert); // 目标链
    tmp = res1[target];
    bool bad = 0;
    tmp2 = ArrayInsert(to_insert, tmp.Getplace(), tmp.Getsize(), bad);
    if (bad) {
      return 1;
    }
    tmp2.Setsize(tmp.Getsize() + 1);
    tmp2.Setblock_nxt(tmp.Getblock_nxt());
    tmp2.Setplace(tmp.Getplace());
    res1[target] = tmp2;
    if (tmp2.Getsize() > limit) {
      SplitBlock(target, tmp2.Getsize());
    }
    return 0;
  }

  bool Fin(Element<T> &to_find) {
    int target = IndexFind(to_find);
    if (!total) {
      return 0;
    }
    Element<T> tmp;
    int flag = 1;
    bool found = 0;
    while (flag) {
      tmp = res1[target];
      flag = ArrayFind(to_find, tmp.Getplace(), tmp.Getsize(), found);
      target = tmp.Getblock_nxt();
      if (!target) {
        break;
      }
    }
    if (!found) {
      return 0;
    }
    return 1; // 1表示找到了
  }

  bool Del(Element<T> to_del) {
    int target = IndexFind(to_del);
    if (total == 0) {
      return 0;
    }
    Element<T> tmp;
    tmp = res1[target];
    bool flag = ArrayDel(to_del, tmp.Getplace(), tmp.Getsize());
    if (flag) { // 删除成功
      int size = tmp.Getsize();
      tmp.Setsize(size - 1);
      res1[target] = tmp;
      if (!(size - 1)) { // 删除后为空
        if (start == target) { // 删除块为开头
          start = tmp.Getblock_nxt();
        } else {
          for (int i = start; i; i = res1[i].Getblock_nxt()) {
            if (res1[i].Getblock_nxt() == target) {
              res1[i].Setblock_nxt(tmp.Getblock_nxt());
              break;
            }
          }
          for (int i = start; i; i = res1[i].Getblock_nxt()) {
            if (res1[i].Getblock_nxt() == total) {
              res1[i].Setblock_nxt(target);
              res1[target] = res1[total];
              break;
            }
          } // 空间重用。
        }
        total--;
      }
    }
    return flag;
  }
bool ArrayFindAll(const Element<T> &to_find, int place, int size, bool &found) {
  Data.read(res2[1], place * largest * sizeof(Element<T>) + 12, size);
  int num = lower_bound(res2 + 1, res2 + size + 1, to_find) - res2;
  for (int i = num; i <= size; i++) {
    if (strcmp(res2[i].element.key, to_find.element.key) == 0) {
      found = 1;
      res2[i].element.Show();
    }
    if (strcmp(res2[i].element.key, to_find.element.key) != 0) {
      return 0;
    }
  }
  return 1;
}

void FindA(Element<T> to_find) {
  int target = IndexFind(to_find);
  if(!total) {
    cout << "\n";
    return;
  }
  Element<T> tmp;
  int flag = 1;
  bool found = 0;
  while (flag) {
    tmp = res1[target];
    flag = ArrayFindAll(to_find, tmp.Getplace(), tmp.Getsize(), found);
    target = tmp.Getblock_nxt();
    if (!target) {
      break;
    }
  }
  if (!found) {
    cout << "\n";
  }
  return;
}

public:
  bool Insert(T to_insert) {
    Element<T> tmp;
    tmp.element = to_insert;
    bool ok = (Ins(tmp) ^ 1);
    return ok;
  }
  T Find(T to_find) {
    Element<T> tmp;
    tmp.element = to_find;
    bool found = Fin(tmp);
    if (!found) {
      T x;
      return x;
    } else {
      return tmp.element;
    }
  }
  bool Delete(T to_del) {
    Element<T> tmp;
    tmp.element = to_del;
    bool ok = Del(tmp);
    return ok;
  }
  void FindAll(T to_find_all) {
    Element<T> tmp;
    tmp.element = to_find_all;
    FindA(tmp);
    return;
  }
  void PrintAll() {
    if (!total) {
      cout << "\n";
      return;
    }//说明没有元素。输出空行。
    for(int i = start; i; i = res1[i].Getblock_nxt()) {
      Data.read(res2[1], res1[i].Getplace() * largest * sizeof(Element<T>) + 12, res1[i].Getsize());
      for(int j = 1; j <= res1[i].Getsize(); j++) {
        res2[j].element.Show();
    }
  }
  return;
  }
  void UpdateIndex() {
    Data.write_info(total, 1);
    Data.write_info(start, 2);
    Data.write_info(current, 3);
    Data.write(res1[1], 12, total);
    return;
  }
};

#endif