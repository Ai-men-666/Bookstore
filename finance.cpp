#include "finance.h"
#include <climits>
#include <vector>
#include "scanner.h"
#include <iostream>
deal deal_max(INT_MAX);
deal deal_min(0);
deal::deal():cnt(0),income(0),outcome(0) {}
deal::deal(int cnt) :cnt(cnt){}
deal::deal(int cnt, int income, int outcome):cnt(cnt),income(income),outcome(outcome) {}
bool operator < (deal &a,deal &b) {
  return a.cnt < b.cnt;
}
bool operator > (deal &a,deal &b) {
  return a.cnt > b.cnt;
}
bool operator <= (deal &a,deal &b) {
  return a.cnt <= b.cnt;
}
bool operator >= (deal &a,deal &b) {
  return a.cnt >= b.cnt;
}
bool operator == (deal &a,deal &b) {
  return a.cnt == b.cnt;
}
std::ostream &operator<<(std::ostream &os, deal a) {
  os << '+' << a.income << '-' << a.outcome << '\n';
}

finance::finance() {
  recorder.initialize("finance_head","finance_body",deal_max,deal_min);
}
int finance::get_cnt() {
  int a;
  recorder.get_info(a,1);
  return a;
}
deal finance::last_deal() {
  deal last(get_cnt());
  recorder.find(last);
  return last;
}
int finance::update_cnt() {
  int a = get_cnt();
  a++;
  recorder.write_info(a,1);
  return a;
}

void finance::add_deal(deal d) {
  deal prev = last_deal();
  int cnt = update_cnt();
  d.cnt = cnt;
  d.income += prev.income;
  d.outcome += prev.outcome;
  recorder.insert(d);
}
void finance::show(Scanner &scanner) {
  if(scanner.is_empty()) {
    std::vector<deal> res;
    recorder.list(res);
    if(res.size() == 0) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
    return;
  }
  int cnt = to_int(scanner.next());
  if(cnt > get_cnt()) {
    throw 0;
  }
  deal tmp(cnt);
  recorder.find(tmp);
  std::cout << tmp;
}

