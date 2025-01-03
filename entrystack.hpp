#ifndef USER_HPP
#define USER_HPP
#include <vector>
#include <string>
#include "account.hpp"
#include "account_manager.hpp"
#include "book_manager.h"
#include "scanner.h"
extern BookManager book_manager;
const int root_rank = 7;
const int worker_rank = 3;
const int customer_rank = 1;
const int visitor_rank = 0;
class entry_stack {
private:
  std::vector<account> stack;
  account_manager account_manager_;
public:
  account cur_account();
  void login(Scanner&);
  void logout();
  void create_account(Scanner&);
  void delete_account(Scanner&);
  void register_account(Scanner&);
  void change_user_password(Scanner&);
};
#endif //USER_HPP
