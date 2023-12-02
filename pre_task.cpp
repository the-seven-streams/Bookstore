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

}; // 第一个数据记录了索引块的总个数。

class Element {
private:
  int value;
  int size; //当为索引块时，size为块内元素的个数
  int block_place;//指示是第几个块。1_base
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
MemoryRiver<Element, 3> Data;//三个参数：总块数，开头，当前数据块存放位置。
int n, largest, limit;

void ArrayInsert(Element &to_insert, int place, int size) {
  Data.read(res2[1], place * largest * sizeof(Element) + 12, size);
  //读出原有数据块。
  int num = upper_bound(res2 + 1, res2 + size + 1, to_insert) - res2;//找到数据位置
  if(!num) {
    Data.write(to_insert, place * largest * sizeof(Element) + 12);
    Data.write(res2[1], place * largest * sizeof(Element) + 12 + sizeof(Element), size);
    return;
  }//说明写入的元素最小
  Data.write(res2[1], place * largest * sizeof(Element) + 12, num);
  Data.write(to_insert, place * largest * sizeof(Element) + 12 + num * sizeof(Element));
  Data.write(res2[num + 1], place * largest * sizeof(Element) + 12 + (num + 1) * sizeof(Element), size - num);
  return;
}

bool ArrayFind(const Element &to_find, int place, int size, bool &found) {
  Data.read(res2[1], place * largest * sizeof(Element) + 12, size);
  int num = lower_bound(res2 + 1, res2 + size + 1, to_find) - res2;
  for(int i = num; i <= size; i++) {
    if(strcmp(res2[i].index, to_find.index) == 0) {
      found = 1;
      cout << res2[i].Getvalue() << ' ';
    }
    if(strcmp(res2[i].index, to_find.index) != 0) {
      return 0;
    }
  }
  return 1;
}

bool ArrayDel(Element &to_del, int place, int size) {
  Data.read(res2[1], place * largest * sizeof(Element) + 12, size);
  int num = lower_bound(res2 + 1, res2 + size + 1, to_del) - res2;
  if(!(to_del == res2[num + 1])) {
    return 0;//没有删除成功。
  }
  if(!num) {
    Data.write(res2[2], place * largest * sizeof(Element) + 12, size - 1);
  } else {
    Data.write(res2[1], place * largest * sizeof(Element) + 12, num);
    Data.write(res2[num + 2], place * largest * sizeof(Element) + 12 + num * sizeof(Element), size - num - 1);
  }
  return 1;
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

void SplitBlock(int num,int start, int size) {
  int mid = size / 2;
  Element origin, new_block;
  Data.read(origin, 12 + (num - 1) * sizeof(Element));
  Data.read(res2[1], origin.Getplace() * largest * sizeof(Element) + 12, size);//读入原有数据块。
  int total, current;
  Data.get_info(total, 1);
  Data.get_info(current, 3);
  total++;
  current++;
  Data.write_info(total, 1);
  Data.write_info(current, 3);
  Data.write(res2[mid], current * largest * sizeof(Element) + 12, size - mid);//写入新的数据块。
  origin = res2[1];
  origin.Setsize(mid);
  origin.Setblock_nxt(total);
  Data.write(origin,  (num - 1) * sizeof(Element)+ 12);//修改原有索引块。
  new_block = res2[mid + 1];
  new_block.Setsize(size - mid);
  new_block.Setblock_nxt(origin.Getblock_nxt());
  new_block.Setplace(current);
  Data.write(new_block, (total - 1) * sizeof(Element) + 12);//新的索引块
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