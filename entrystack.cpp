#include "entrystack.hpp"
#include <algorithm>
extern BookManager book_manager;
account entry_stack::cur_account() {
  if(stack.empty()) {
    return account();
  }
  return stack.back();
}
void entry_stack::login(Scanner &scanner) {
  string id = scanner.next();
  if(scanner.is_empty()) {
    account tmp;
    if(!account_manager_.find_and_get(id,tmp)) {
      throw 0;
    }
    if(tmp.privilege >= cur_account().privilege) {
      throw 0;
    }
    stack.push_back(tmp);
    return;
  }
  string pd = scanner.next();
  account tmp;
  if(!account_manager_.find_and_check(id,pd,tmp)) {
    throw 0;
  }
  stack.push_back(tmp);
}
void entry_stack::logout() {
  if(cur_account().privilege < 1) {
    throw 0;
  }
  book_manager.delete_select_book();
  if(stack.empty()) {
    throw 0;
  }
  stack.pop_back();
}
void entry_stack::create_account(Scanner &scanner) {
  if(cur_account().privilege < 3) {
    throw 0;
  }
  string id = scanner.next();
  if(account_manager_.find(id)) {
    throw 0;
  }
  string pd = scanner.next();
  int privilege = to_int(scanner.next());
  if(privilege != 0 && privilege != 1 && privilege != 3 && privilege != 7) {
    throw 0;
  }
  if(privilege >= cur_account().privilege) {
    throw 0;
  }
  string name = scanner.next();
  if(!scanner.is_empty()) {
    throw 0;
  }
  account_manager_.create(id,pd,privilege,name);
}
void entry_stack::delete_account(Scanner &scanner) {
  if(cur_account().privilege < 7) {
    throw 0;
  }
  string id = scanner.next();
  if(!scanner.is_empty()) {
    throw 0;
  }
  account tmp(id);
  auto it = std::find(stack.begin(),stack.end(),tmp);
  if(it != stack.end()) {
    throw 0;
  }
  if(!account_manager_.find(id)) {
    throw 0;
  }
  account_manager_.Delete(id);
}
void entry_stack::register_account(Scanner &scanner) {
  string id = scanner.next();
  string pd = scanner.next();
  string name = scanner.next();
  if(!scanner.is_empty()) {
    throw 0;
  }
  account_manager_.Register(id,pd,name);
}
void entry_stack::change_user_password(Scanner &scanner) {
  if(cur_account().privilege < 1) {
    throw 0;
  }
  string id = scanner.next();
  string pd = scanner.next();
  string new_pd;
  if(scanner.is_empty()) {
    if(cur_account().privilege < 7) {
      throw 0;
    }
    account_manager_.change_passwd(id,pd);
    return;
  }
  new_pd = scanner.next();
  if(!scanner.is_empty()) {
    throw 0;
  }
  account_manager_.change_passwd(id,pd,new_pd);
}


