#include <iostream>
#include "scanner.h"
#include "entrystack.hpp"
char select_book[20]{};
int main() {
  string line;
  string order;
  entry_stack stack;
  Scanner scanner;
  while(!std::cin.eof()) {
    try {
      std::getline(std::cin,line);
      scanner.initialise(line);
      order = scanner.next();
      if(order == "exit") {
        exit(0);
        continue;
      }
      if(order == "quit") {
        exit(0);
        continue;
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


      throw 0;
    }catch (...) {
      std::cout << "Invalid\n";
    }
  }
}
