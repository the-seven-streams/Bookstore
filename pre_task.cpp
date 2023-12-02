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
  int size; //当为索引块时，size为块内元素的个数
  int block_place;//指示是第几个块。1_base
  int nxt;//块内后继。1_base
  int start;//指示块内头结点的位置。1_base
  int block_nxt;//索引块内后继。1_base

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
  void SpecialInitial() {
    value = minus_inf;
    cin >> index;
    int len = strlen(index);
    memset(index + len, '\0', sizeof(index) - len);
    return;
  }
  int Getstart() { return start; }
  void Setstart(int x) {
    start = x;
    return;
  }
  int Getnxt() { return nxt; }
  void Setnxt(int x) {
    nxt = x;
    return;
  }
  int Getblock_nxt() { return block_nxt; }
  void Setblock_nxt(int x) {
    block_nxt = x;
    return;
  }
  bool operator<(const Element &a) const {
    if (strcmp(index, a.index) != 0)
      return strcmp(index, a.index) < 0 ? 1 : 0;
    return value < a.value;
  }
  bool operator>(const Element &a) const {
    if (strcmp(index, a.index) != 0)
      return strcmp(index, a.index) > 0 ? 1 : 0;
    return value > a.value;
  }
  bool operator==(const Element &a) const {
    return (strcmp(index, a.index) == 0) && value == a.value;
  }
} res_element;

Element res1[1000], res2[1000]; // 所有res1用于索引块操作。res2用于数据块操作。
MemoryRiver<Element, 3> Data;//三个参数：总块数，开头，当前数据块位置。
int n, largest, limit;

bool LinkInsert(Element to_insert, int num, int start, int size) {
  Data.read(res2[1], num * largest * sizeof(Element) + 12, size); // 读出数据块
  bool flag = 0;
  int last = 0;
  for (int i = start; i; i = res2[i].Getnxt()) {
    if (to_insert < res2[i]) {
      flag = 1;
      to_insert.Setnxt(i);
      res2[last].Setnxt(size + 1);
      if (last) {
        Data.write(res2[last], num * largest * sizeof(Element) + 12 +
                                   (last - 1) * sizeof(Element));
      } // 如果last为0，说明插入在了头结点。不需要修改前置节点。
      Data.write(to_insert,
                 num * largest * sizeof(Element) + 12 + size * sizeof(Element));
      break;
    }
    last = i;
  }
  if (!flag) {
    res2[last].Setnxt(size + 1);
    if (last) {
      Data.write(res2[last], num * largest * sizeof(Element) + 12 +
                                 (last - 1) * sizeof(Element));
    }
    Data.write(to_insert,
               num * largest * sizeof(Element) + 12 + size * sizeof(Element));
  } // 修改前一个数值和后一个。
  for(int i = start; i; i = res2[i].Getnxt()) {
    cout << res2[i].index << " " << res2[i].Getnxt() << " " << res2[i].Getvalue() << endl;
  }
  if (last) {
    return 0;
  } else {
    return 1; // 插入在了第一个位置上。提醒修改开头。
  }
}

bool LinkFind(const Element &to_find, int num, int start, int size, bool &flag) {
  Data.read(res2[1], num * largest * sizeof(Element) + 12, size);
  for (int i = start; i; i = res2[i].Getnxt()) {
    if (strcmp(to_find.index, res2[i].index) == 0) {
      flag = 1;
      cout << res2[i].Getvalue() << ' ';
    }
    if (strcmp(to_find.index, res2[i].index) < 0) {
      return 0;
    } // 如果大于，说明后面的都不用找了。
  }
  return 1;
}

int LinkDel(const Element &to_del, int num, int start, int size) {
  Data.read(res2[1], num * largest * sizeof(Element) + 12, size);
  int del = 0;
  int last = 0;
  for (int i = start; i; i = res2[i].Getnxt()) {
    if (to_del == res2[i]) {
      del = i; // 找到了要删除的元素的序号。
      res2[last].Setnxt(res2[i].Getnxt()); // 修改前置节点的指针
      break;
    }
    last = i;
  }
  if (del) {
    for (int i = start; i; i = res2[i].Getnxt()) {
      if (res2[i].Getnxt() == size) {
        res2[i].Setnxt(del);
        Data.write(res2[size], num * largest * sizeof(Element) + 12 +
                                   (del - 1) * sizeof(Element));
        // 覆写，空间重用。
        break;
      }
    }
    if (last) {
      Data.write(res2[last], num * largest * sizeof(Element) + 12 +
                                 (last - 1) * sizeof(Element));
      // 修改前置节点。
      return -1; // 普通删除
    } else {
      return res2[del].Getnxt(); // 删除了头结点。指示新的头结点。
    }
  }
  return 114514; // 没有找到。
}

int IndexFind(const Element &x) {
  int start, total;
  Data.get_info(start, 2);
  Data.get_info(total, 1);
  Data.read(res1[1], 12, total);
  int last = start;
  for (int i = start; i; i = res1[i].Getblock_nxt()) {
    if (x < res1[i]) {
      return last;
    }
    last = i;
  }
  return last;
}//这个函数的目的是找到目标块。

void SplitBlock(int place,int start, int size) {
  int mid = size / 2;
  Element res3[500];
  Element res4[500];
  Data.read(res2[1], place * largest * sizeof(Element) + 12, size);//读入原有数据块。
  int count;
  int i = start;
  for(count = 1; count <= mid; i = res2[i].Getnxt(), count++){
    res3[count] = res2[i];
    res3[count].Setnxt(count + 1);
    cout << res3[count].index << "I3" <<endl;
  }
  res3[mid].Setnxt(0);//将原有块的一半存入res3中。
  count = 1;
  for(count = 1; i; i = res2[i].Getnxt(), count++){
    res4[count] = res2[i];
    res4[count].Setnxt(count + 1);
    cout << res4[count].index << " " << res4[count].Getnxt() <<"I4" <<endl;
  }
  res4[size - mid].Setnxt(0);
  int total, current;
  Data.get_info(total, 1);
  Data.get_info(current, 3);
  total++;
  current++;
  Data.write_info(total, 1);//修改total。
  Data.write_info(current, 3);
  res4[1].Setsize(size - mid);
  res4[1].Setstart(1);
  Element origin;
  Data.read(origin, (place - 1) * sizeof(Element) + 12);//取出原有索引节点。
  res4[1].Setblock_nxt(origin.Getblock_nxt());
  res4[1].Setplace(current);
  origin.Setblock_nxt(total);
  origin.Setsize(mid);
  origin.Setstart(1);
  Data.write(res3[1], place * largest * sizeof(Element) + 12, mid);
  Data.write(origin, (place - 1) * sizeof(Element) + 12);
  Data.write(res4[1], current * largest * sizeof(Element) + 12, size - mid);
  //写入数据块。位置应当为current。指示当前已经写了多少个数据块。
  Data.write(res4[1], (total - 1) * sizeof(Element) + 12);
  return;
}

void MergeBlock(int a,int b,int size_a, int size_b, int start_a, int start_b) {//a中的元素全部小于b中的元素。
  Data.read(res1[1], a * largest * sizeof(Element) + 12, size_a);
  Data.read(res2[1], b * largest * sizeof(Element) + 12, size_b);
  int last;
  for(int i = start_a; i; i = res1[i].Getnxt()) {
    last = i;
  }
  res1[last].Setnxt(start_b + size_a);//修改第一个块中的尾指针。
  last = 0;
  for(int i = start_a;i; i = res2[i].Getnxt()) {
    res1[i + size_a] = res2[i];
    res1[i + size_a].Setnxt(res2[i].Getnxt() + size_a);
    last = i;
  }
  res1[last + size_a].Setnxt(0);
  Data.write(res1[1],a * largest * sizeof(Element) + 12, size_a + size_b);
  Element x, y;
  Data.read(x, 12 + (a - 1) *sizeof(Element));
  Data.read(y, 12 + (b - 1) * sizeof(Element));
  x.Setblock_nxt(y.Getblock_nxt());//将b并吞。
  Data.write(x, 12 + (a - 1) * sizeof(Element));
  int total;
  Data.get_info(total, 1);
  int start;
  Data.get_info(start, 2);
  Element tmp[1000];
  Data.read(tmp[1], 12, total);
  int end;
  for(int i = start; i; i = tmp[i].Getblock_nxt()) {
    if(tmp[i].Getblock_nxt() == total) {
      tmp[i].Setblock_nxt(b);
      end = i;
      break;
    }
  }
  Data.write(tmp[end], 12 + (end - 1) * sizeof(Element));//修改。
  Data.write(tmp[total], 12 + (b - 1) * sizeof(Element));//覆写空间。
  Data.write_info(total - 1, 1);//修改总数。
  return;
} 

void Ins(Element to_insert) {
  int total, start, current;
  Data.get_info(total, 1);
  Data.get_info(start, 2);
  Data.get_info(current, 3);
  if(total == 0) {
    total++;
    current++;
    to_insert.Setstart(1);
    to_insert.Setplace(current);
    to_insert.Setsize(1);
    Data.write_info(total, 1);
    Data.write_info(total, 2);
    Data.write(to_insert, 12, 1);
    Data.write(to_insert, 12 + largest * sizeof(Element));
    return;
  }

  Element tmp;
  int target = IndexFind(to_insert);
  Data.read(tmp, 12 + (target - 1) * sizeof(Element));
  int flag = LinkInsert(to_insert, target, tmp.Getstart(), tmp.Getsize());
  int size = tmp.Getsize();
  if(flag) {//指示需要修改索引块。
    int n = size + 1;
    to_insert.Setstart(n);
    to_insert.Setblock_nxt(tmp.Getblock_nxt());
    to_insert.Setnxt(tmp.Getstart());
    tmp = to_insert;
  }
  tmp.Setsize(size + 1);
  Data.write(tmp, 12 + (target - 1) * sizeof(Element));
  if(size + 1 > limit) {
    cout << size +1 << "s"<<endl;
    SplitBlock(target, tmp.Getstart(), size + 1);
  }
  return;
}

void Fin(Element to_find) {
  int total, start;
  int target = IndexFind(to_find);
  Data.get_info(total, 1);
  Data.get_info(start, 2);
  Element tmp;
  int flag = 1;
  bool found = 0;
  while(flag) {
  cout << target << endl;
  Data.read(tmp, 12 + (target - 1) * sizeof(Element));
  flag = LinkFind(to_find, target, tmp.Getstart(), tmp.Getsize(), found);
  target = tmp.Getblock_nxt();
    if(!target) {
    break;
    }
  }
  if(!found) {
    cout << "null";
  }
  cout << '\n';
  return;
}

void Del(Element to_del) {
  int total, start;
  int target = IndexFind(to_del);//找到目标块。
  cout <<target << endl;
  assert(target == 2);
  Data.get_info(total, 1);
  Data.get_info(start, 2);
  Element tmp;
  int size = res1[target].Getsize();
  int x = LinkDel(to_del, target, res1[target].Getstart(), res1[target].Getsize());
  if(x == 114514) {
    return;
  }//如删。
  if(size - 1) {//说明这个块还没有被删干净。
    res1[target].Setsize(size - 1);//说明删除成功，修改块大小。
    if(x > 0) {//说明删除了头结点。
      tmp = res2[x];//指示新的头结点。
      tmp.Setblock_nxt(res1[target].Getblock_nxt());
      tmp.Setsize(size - 1);
      tmp.Setstart(x);
    } else {
      tmp = res1[target];
    }
    Data.write(tmp, 12 + (target - 1) * sizeof(Element));
    return;
  } else {
    if(target == start) {//说明第一个块被删空了。
      start = res1[target].Getblock_nxt();
      Element tmp2;
      Data.read(tmp2, 12 + (total - 1) * sizeof(Element));//取出最后一个块。
      for(int i = start; i; i = res1[i].Getblock_nxt()) {
        if(res1[i].Getblock_nxt() == total) {
          res1[i].Setblock_nxt(target);
          Data.write(res1[i], 12 + (i - 1) * sizeof(Element));
          Data.write(res1[total], 12 + (target - 1) * sizeof(Element));
          //覆写，空间重用。
          break;
        }
      }
      total--;
      Data.write_info(total, 1);//写入最新的总数。
      Data.write_info(start, 2);//写入最新的开头。
    } else {
      int i;
      for(i = start; i; i = res1[i].Getblock_nxt()) {
        if(res1[i].Getblock_nxt() == target) {
          res1[i].Setblock_nxt(res1[target].Getblock_nxt());
          break;
        }//将这个块的索引删去。
      }
      int last = i;//指示前一个块。
      for(i = start; i; i = res1[i].Getblock_nxt()) {
        if(res1[i].Getblock_nxt() == total) {
          res1[i].Setblock_nxt(target);
          Data.write(res1[i], 12 + (i - 1) * sizeof(Element));
          Data.write(res1[total], 12 + (target - 1) * sizeof(Element));
          //覆写，空间重用。
          break;
        }
      }
      Data.write(res1[last], 12 + (last - 1) * sizeof(Element));
      total--;
      Data.write_info(total, 1);//写入最新的总数。
    }
  }
  return;
}

void check() {
  int start, total;
  Data.get_info(start, 2);
  Data.get_info(total, 1);
  Data.read(res1[1], 12, total);
  for(int i = start; i; i = res1[i].Getblock_nxt()) {
    cout << res1[i].index << res1[i].Getvalue() <<res1[i].Getsize() <<endl;
  }
  return;
}
int main() {
  cin >> n;
  Data.initialise("Data.txt");
  /*Element test;
  Data.read(test, 12 + sizeof(Element));
  cout << test.Getblock_nxt() << endl;
  assert(0);*/
  int tmp;
  Data.get_info(tmp, 1);
  largest = 500;
  limit = 2;
  for (int i = 1; i <= n; ++i) {
    string op;
    cin >> op;
    switch (op[0]) {
      case 'i': {
        res_element.Initial();
        Ins(res_element);
        break;
      }
      case 'f': {
        res_element.SpecialInitial();
        Fin(res_element);
        break;
      }
      case 'd': {
        res_element.Initial();
        Del(res_element);
        break;
      }
      case 'c': {
        check();
        break;
      }
    }
  }
  return 0;
}