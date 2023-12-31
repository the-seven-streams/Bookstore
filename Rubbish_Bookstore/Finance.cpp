#include "Finance.hpp"
#include <ios>
MemoryRiver<double, 1> finance("finance.txt");
MemoryRiver<double, 0> finance_total("finance_total.txt");
void AddDeal(double value1) {
  int total;
  double value = value1;
  finance.get_info(total, 1); // 检定当前操作总次数。
  finance.write(value, 4 + total * sizeof(double), 1); // 写入新的交易记录。
  total++;
  finance.write_info(total, 1);
  if (value > 0) {
    double res;
    finance_total.read(res, 0, 1);
    res += value;
    finance_total.write(res, 0, 1);
  } else {
    double res;
    finance_total.read(res, sizeof(double), 1);
    res += value;
    finance_total.write(res, sizeof(double), 1);
  }
  return;
}
void ShowFinance(int n) {
  int total;
  finance.get_info(total, 1); // 检定当前操作总次数。
  if (n > total) {
    throw(0);
  }
  double income = 0;
  double cost = 0;
  if (n) {
    double *res = new double[n];
    finance.read(res[0], 4 + (total - n) * sizeof(double), n);
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
    finance_total.read(cost, sizeof(double), 1);
  }
  std::cout << "+ ";
  std::cout << std::fixed << std::setprecision(2) << income << " ";
  std::cout << "- ";
  std::cout << std::fixed << std::setprecision(2) << fabs(cost) << std::endl;
  return;
}
