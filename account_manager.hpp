#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP
#include "store.hpp"
#include "scanner.h"
#include "account.hpp"
const account max_account("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
const account min_account{};
class account_manager {
public:
  account_manager();
  void Register(string &id,string &pd,string &name);
  void change_passwd(string &id,string &pd,string &new_pd);
  void change_passwd(string &id,string&new_pd);
  void create(string &id,string &pd,int privilege,string &name);
  void Delete(string &id);
  bool find_and_check(string &id,string &pd,account &);
  bool find(string &id);
  bool find_and_get(string &id,account &t);
private:
  block_operator<account> store{};
};
#endif //ACCOUNT_MANAGER_HPP
