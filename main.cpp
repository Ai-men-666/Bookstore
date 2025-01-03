#include <iomanip>
#include <iostream>
#include "book_manager.h"
#include "scanner.h"
#include "entrystack.hpp"
#include "finance.h"
finance finance_recorder{};
entry_stack stack{};
BookManager book_manager;
int main() {
  string line;
  string order;
  Scanner scanner;
  std::cout << std::fixed << std::setprecision(2);
  int cnt = 0;
  while(!std::cin.eof()) {
    cnt++;
    try {
      std::getline(std::cin,line);
      scanner.initialise(line);
      if(scanner.is_empty()) {
        continue;
      }
      order = scanner.next();
      if(order == "exit") {
        return 0;
      }
      if(order == "quit") {
        return 0;
      }
      if(order == "su") {
        stack.login(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "logout") {
        stack.logout();
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "register") {
        stack.register_account(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "passwd") {
        stack.change_user_password(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "useradd") {
        stack.create_account(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "delete") {
        stack.delete_account(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "select") {
        book_manager.select(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "show") {
        Scanner scanner_ = scanner;
        if(scanner_.is_empty() || scanner_.next() != "finance") {
          book_manager.show(scanner);
        }else {
          finance_recorder.show(scanner_);
        }
        if(!(scanner.is_empty() || scanner_.is_empty())) {
          throw 0;
        }
        continue;
      }
      if(order == "buy") {
        book_manager.buy(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "modify") {
        book_manager.modify(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      if(order == "import") {
        book_manager.import(scanner);
        if(!scanner.is_empty()) {
          throw 0;
        }
        continue;
      }
      throw 0;
    }catch (...) {
      std::cout << "Invalid\n";
    }
  }
  return 0;
}