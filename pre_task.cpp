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
  int nxt;
  int start;
  int block_nxt;
public:
  char index[64];
  Element() {
    value = 0;
    size = 0;
    block_place = 0;
    block_nxt = 0;
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
  int Getstart() {
    return start;
  }
  void Setstart(int x) {
    start = x;
    return;
  }
  int Getnxt() {
    return nxt;
  }
  void Setnxt(int x) {
    nxt = x;
    return;
  }
  int Getblock_nxt() {
    return block_nxt;
  }
  void Setblock_nxt(int x) {
    block_nxt = x;
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
MemoryRiver<Element, 2> Data;
int n, largest, limit;

bool LinkInsert(Element to_insert, int num, int start, int size) {
  Data.read(res2[1], num * largest * sizeof(Element) + 8, size);//读出数据块
  bool flag = 0;
  int last = 0;
  for(int i = start; i; i = res2[i].Getnxt()) {
    if(to_insert < res2[i]) {
      flag = 1;
      to_insert.Setnxt(i);
      res2[last].Setnxt(size + 1);
      if(last) {
        Data.write(res2[last], num * largest * sizeof(Element) + 8 + (last - 1) * sizeof(Element));
      }//如果last为0，说明插入在了头结点。不需要修改前置节点。
      Data.write(to_insert, num * largest * sizeof(Element) + 8 + size * sizeof(Element));
      break;
    }
    last = i;
  }
  if(!flag) {
    res2[last].Setnxt(size + 1);
    if(last) {
      Data.write(res2[last], num * largest * sizeof(Element) + 8 + (last - 1) * sizeof(Element));
    }
      Data.write(to_insert, num * largest * sizeof(Element) + 8 + size * sizeof(Element));
  }//修改前一个数值和后一个。
  if(last) {
    return 0;
  } else {
    return 1;//插入在了第一个位置上。提醒修改开头。
  }
}

bool LinkFind(const Element &to_find, int num, int start, int size) {
  Data.read(res2[1], num * largest * sizeof(Element) + 8, size);
  for(int i = start; i; i = res2[i].Getnxt()) {
    if(to_find == res2[i]) {
      cout << res2[i].Getvalue() << ' ';
    }
    if(to_find > res2[i]) {
      return 0;
    }//如果大于，说明后面的都不用找了。
  }
  return 1;
}

int LinkDel(const Element &to_del, int num, int start, int size) {
  Data.read(res2[1], num * largest * sizeof(Element) + 8, size);
  int del = 0;
  int last = 0;
  for(int i = start; i; i = res2[i].Getnxt()) {
    if(to_del == res2[i]) {
      del = i;//找到了要删除的元素的序号。
      res2[last].Setnxt(res2[i].Getnxt());//修改前置节点的指针
      break;
    }
    last = i;
  }
  if(del) {
    for(int i = start; i; i = res2[i].Getnxt()) {
      if(res2[i].Getnxt() == size) {
        res2[i].Setnxt(del);
        Data.write(res2[size], num * largest * sizeof(Element) + 8 + (del - 1) * sizeof(Element));
        //覆写，空间重用。
        break;
      }
    }
    if(last) {
      Data.write(res2[last], num * largest * sizeof(Element) + 8 + (last - 1) * sizeof(Element));
      //修改前置节点。
      return -1;//普通删除
    } else {
      return res2[del].Getnxt();//删除了头结点。指示新的头结点。
    } 
  } 
  return 114514;//没有找到。
}

int IndexFind(const Element &x) {
  int start, total;
  Data.get_info(start, 2);
  Data.get_info(total, 1);
  Data.read(res1[1], 8, total);
  int last = start;
  for(int i = start; i; i = res1[i].Getblock_nxt()) {
    if(x < res1[i]) {
      return last;
    }
    last = i;
  }
  return last;//找到目标块。
}

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
      Fin(res_element);
      break;
    }
    }
  }
}