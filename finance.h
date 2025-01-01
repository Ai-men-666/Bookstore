#ifndef FINANCE_H
#define FINANCE_H
#include "scanner.h"
#include "store.hpp"
struct deal {
  int cnt;
  double income,outcome;
  deal();
  deal(int cnt);
  deal(int cnt,int income,int outcome);
};

bool operator < (deal &a,deal &b);
bool operator > (deal &a,deal &b);
bool operator <= (deal &a,deal &b);
bool operator >= (deal &a,deal &b);
bool operator == (deal &a,deal &b);
std::ostream& operator<<(std::ostream&,deal);
class finance {
public:
  finance();
  int get_cnt();
  int update_cnt();//返回更新后的cnt
  deal last_deal();
  void add_deal(deal);
  void show(Scanner&);
  block_operator<deal> recorder;
};
#endif //FINANCE_H
