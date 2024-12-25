
#ifndef USER_HPP
#define USER_HPP
#include <vector>
extern const int root_rank = 7;
extern const int worker_rank = 3;
extern const int customer_rank = 1;
extern const int visitor_rank = 0;
class account {
private:
  int privilege = -1;
  char name[30]{};
  char password[30]{};
public:
};
class entry_stack {
private:
  char book[60] = {-1};
  std::vector<account> stack;
  account cur;
public:
  account cur_account();
  void initialise();
  void add_root();
  void add_worker();
  void add_customer();
  void add_visitor();
  void login();
  void logout();
  void create_account();
  void delete_account();
  void register_account();
  void change_user_password();
};
#endif //USER_HPP
