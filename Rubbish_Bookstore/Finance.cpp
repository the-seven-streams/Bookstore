#include "Finance.hpp"
#include <ios>
MemoryRiver<long double, 1> finance("finance.txt");
MemoryRiver<long double, 0> finance_total("finance_total.txt");
void AddDeal(long double value1) {
  int total;
  long double value = value1;
  finance.get_info(total, 1); // 检定当前操作总次数。
  finance.write(value, 4 + total * sizeof(long double), 1); // 写入新的交易记录。
  total++;
  finance.write_info(total, 1);
  if (value > 0) {
    long double res;
    finance_total.read(res, 0, 1);
    res += value;
    finance_total.write(res, 0, 1);
  } else {
    long double res;
    finance_total.read(res, sizeof(long double), 1);
    res += value;
    finance_total.write(res, sizeof(long double), 1);
  }
  return;
}
void ShowFinance(int n) {
  int total;
  finance.get_info(total, 1); // 检定当前操作总次数。
  if (n > total) {
    throw(0);
  }
  long double income = 0;
  long double cost = 0;
  if (n) {
    long double *res = new long double[n];
    finance.read(res[0], 4 + (total - n) * sizeof(long double), n);
    for (int i = 0; i < n; i++) {
      if (res[i] > 0) {
        income += res[i];
      } else {
        cost += res[i];
      }
    }
    delete[] res;
  } else {
    finance_total.read(income, 0, 1);
    finance_total.read(cost, sizeof(long double), 1);
  }
  std::cout << "+ ";
  std::cout << std::fixed << std::setprecision(2) << income << " ";
  std::cout << "- ";
  std::cout << std::fixed << std::setprecision(2) << -(cost) << std::endl;
  return;
}
