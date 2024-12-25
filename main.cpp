#include <iostream>
#include "scanner.h"
#include "user.hpp"
int main() {
  string line;
  string order;
  entry_stack stack;
  Scanner scanner;
  try {
    while(!std::cin.eof()) {
      std::getline(std::cin,line);
      scanner.initialise(line);
      order == scanner.next();
      if(order == "exit") {
        exit(0);
      }
      if(order == "quit") {
        exit(0);
      }
      if(order == "")
    }
  }catch (int) {
    std::cout << "Invalid\n";
  }
}
