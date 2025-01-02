#include "finance.h"
#include <climits>
#include "scanner.h"
#include <iostream>
extern entry_stack stack;
deal::deal():cnt(0),income(0),outcome(0) {}
deal::deal(int cnt) :cnt(cnt){}
deal::deal(int cnt, int income, int outcome):cnt(cnt),income(income),outcome(outcome) {}
deal deal_max(INT_MAX);
deal deal_min(0);
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
deal &operator++(deal &a) {
  a.cnt++;
  return a;
}

std::ostream &operator<<(std::ostream &os, deal a) {
  os << "+ " << a.income << " - " << a.outcome << '\n';
}

finance::finance() {
  deal_max.cnt = INT_MAX;
  deal_max.income = 0;
  deal_max.outcome = 0;
  deal_min.income = 0;
  deal_min.outcome = 0;
  deal_min.cnt = 0;
  recorder.initialize("finance_head","finance_body",deal_max,deal_min);
  deal d;
  d.cnt = 1;d.income = 0;d.outcome = 0;
  recorder.insert(d);
  update_cnt();
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
  if(stack.cur_account().privilege < 7) {
    throw 0;
  }
  if(scanner.is_empty()) {
    if(last_deal().cnt == 1) {
      std::cout << '\n';
    }else {
      std::cout << last_deal();
    }
    return;
  }
  int cnt = to_int(scanner.next());
  if(cnt == 0) {
    std::cout << '\n';
    return;
  }
  if(cnt > get_cnt() - 1) {
    throw 0;
  }
  int sum = get_cnt();
  deal tmp(sum - cnt);
  recorder.find(tmp);
  deal res;
  res.income = last_deal().income - tmp.income;
  res.outcome = last_deal().outcome - tmp.outcome;
  std::cout << res;
}

