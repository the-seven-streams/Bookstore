#include <algorithm>
#include <bits/stdc++.h>
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
  Element() = default;
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
    return index == a.index && value == a.value;
  }
} res_element;

Element res1[1000], res2[1000]; // 所有res1用于索引块操作。res2用于数据块操作。
MemoryRiver<Element, 1> Data;
int n, largest, limit;

void Ins(Element x) {
  int total;
  Data.get_info(total, 1);
  if (!total) {
    Data.write_info(1, 1);
    Data.write(x, 4 + sizeof(Element) * largest); // 写入数据块。
    x.Setsize(1);
    x.Setplace(1);
    Data.write(x, 4); // 写入索引块。
    return;
  } // 说明一个元素也没有。直接写入索引块。
  Data.read(res1[1], 4, total); // 将索引块所有信息读入。
  int number = (upper_bound(res1, res1 + total, x)) -
               res1; // 找到第一个大于x的元素的索引的位置。
  if (!number) {
    number = 1;
  } // 说明这是最小的元素。
  Data.read(res2[1], 4 + sizeof(Element) * res1[number].Getplace(),
            res1[number].Getsize()); // 将数据块所有信息读入。
  int number2 = upper_bound(res2, res2 + res1[number].Getsize(), x) -
                res2; // 记录第一个比x大的元素。
  if (!number2) {
    res2[0] = x;
    Data.write(res2[0],
               4 + sizeof(Element) * largest * res1[number].Getplace(),
               res1[number].Getsize() + 1);
    res2[0].Setsize(res1[number].Getsize() + 1);
    res2[0].Setplace(1); // 准备将res0替换原因索引块。
    Data.write(res2[0], 4);
  } else { // 插入元素是该索引链中最小的元素。
    Data.write(res2[1],
               4 + sizeof(Element) * largest * res1[number].Getplace(),
               number2); // 插入小于其的元素。
    Data.write(x,
               4 + sizeof(Element) * (largest * res1[number].Getplace() +
                                      number2)); // 插入元素。
    Data.write(res2[number2 + 1],
               4 + sizeof(Element) *
                       (largest * res1[number].Getplace()+ number2 + 1),
               res1[number].Getsize() - number2); // 插入大于其的元素。
    int res_size = res1[number].Getsize();
    res1[number].Setsize(res_size + 1); // 修改索引大小。
    Data.write(res1[number], 4 + sizeof(Element) * (number - 1)); // 修改索引。
  }
  if (res1[number].Getsize() > limit) { // 开始裂块操作。
    int mid = res1[number].Getsize() / 2;
    res1[number].Setsize(
        mid); // 直接修改索引就可以了。但是下一个块的位置需要考虑。
    Element res3[mid + 5];
    for (int i = mid + 1; i <= res1[number].Getsize(); i++) {
      res3[i - mid - 1] = res2[i];
    } // 将之后的所有内容存储到res3中。
    Data.write(res1[1], 4, number); // 之前number的内容正常写入。
    Data.write_info(total + 1, 1);  // 索引块的总数加一。
    total++;
    Data.write(res3[0], 4 + sizeof(Element) * largest * (total),
               (res1[number].Getsize() - mid)); // 写入新的数据块。
    res3[0].Setsize(res1[number].Getsize() - mid);
    res3[0].Setplace(total); // 准备写入新的索引块。
    Data.write(res1[1], 4, number);
    Data.write(res3[0], 4 + sizeof(Element) * (number));
    Data.write(res1[number + 1], 4 + sizeof(Element) * (number + 1),
               total - number - 1); // 写入新的索引块。
  }
  return;
}

void Find(Element x) {
  int total;
  Data.get_info(total, 1);
  if (!total) {
    cout << "F1";
    cout << "null" << '\n';
    return;
  } // 说明啥也没有。
  Data.read(res1[1], 4, total);
  int number = (upper_bound(res1 + 1, res1 + total + 1, x)) - res1 - 1;
  if (!number) {
    cout << "null" << '\n';
    return;
  } // 说明查询索引太小了。
  bool flag = 0;
  for (int i = number; i <= total; i++) {
    Data.read(res2[1], 4 + sizeof(Element) * largest * res1[i].Getplace(),
              res1[i].Getsize());
    for (int j = 1; j <= res1[i].Getsize(); j++) {
      cout << res1[i].Getsize();
      if (res2[j].index == x.index) {
        flag = 1;
        cout << res2[j].Getvalue() << ' ';//找到了。
      }
      if (res2[j].index < x.index) {
        if (!flag) {
          cout << "F2";
          cout << "null";
        }
        cout << '\n';
        return;
      }
    }
  }
  if (!flag) {
    cout << "F3";
    cout << "null";
  }
  cout << '\n';
  return;
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
      Find(res_element);
      break;
    }
    }
  }
}