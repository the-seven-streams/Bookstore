#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
#include <ostream>
#include <unistd.h>
using namespace std;

const int minus_inf = -2147483648;
template <class T, int info_len = 2> class MemoryRiver {
private:
  fstream file;
  string file_name;
  int sizeofT = sizeof(T);

public:
  MemoryRiver() = default;

  MemoryRiver(const string &file_name) : file_name(file_name) {}

  void initialise(string FN = "") {
    if (FN != "")
      file_name = FN;
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
  void write(T &t, int place, int size = 1) {
    file.open(file_name);
    file.seekp(place);
    file.write(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
    return;
  }
  void read(T &t, const int index, int size = 1) {
    file.open(file_name);
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&t), sizeofT * size);
    file.close();
    return;
  }

  // 用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(T &t, const int index) {
    file.open(file_name);
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&t), sizeofT);
    file.close();
    return;
  }
}; // 第一个数据记录了索引块的总个数。

class Element {
private:
  int value;
  int size; // 当为索引块时，size为块内元素的个数
  int block_place;

public:
  char index[64];
  Element() {
    value = 0;
    size = 0;
    block_place = 0;
    memset(index, '\0', sizeof(index));
  }
  void Initial() {
    cin >> index;
    cin >> value;
    return;
  }
  void Setsize(int x) {
    size = x;
    return;
  }
  int Getsize() { return size; }
  void Getindex(char *x) {
    strcpy(x, index);
    return;
  }
  int Getvalue() { return value; }
  int Getplace() { return block_place; }
  void Setplace(int x) {
    block_place = x;
    return;
  }
  void Print() {
    cout << value << ' ' << endl;
    return;
  }
  void SpecialInitial() {
    value = minus_inf;
    cin >> index;
    return;
  }
  bool operator<(const Element &a) const {
    if (index != a.index)
      return index < a.index;
    return value < a.value;
  }
  bool operator>(const Element &a) const {
    if (index != a.index)
      return index > a.index;
    return value > a.value;
  }
  bool operator==(const Element &a) const {
    return (strcmp(index, a.index) == 0) && value == a.value;
  }
} res_element;

Element res1[1000], res2[1000]; // 所有res1用于索引块操作。res2用于数据块操作。
MemoryRiver<Element, 1> Data;
int n, largest, limit;

int main() {
  cin >> n;
  Data.initialise("Data.txt");
  int tmp;
  Data.get_info(tmp, 1);
  largest = 500;
  limit = 480;
  for (int i = 1; i <= n; ++i) {
    string op;
    cin >> op;
    switch (op[0]) {
    case 'I': {
      res_element.Initial();
      Ins(res_element);
      break;
    }
    case 'F': {
      res_element.SpecialInitial();
      Find(res_element);
      break;
    }
    }
  }
}