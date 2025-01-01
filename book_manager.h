#ifndef BOOK_MANAGER_H
#define BOOK_MANAGER_H
#include "book.h"
#include "store.hpp"
#include "scanner.h"
class BookManager {
  block_operator<ISBN_to_id> ISBN_finder;
  block_operator<name_to_id> name_finder;
  block_operator<author_to_id> author_finder;
  block_operator<keyword_to_id> key_word_finder;
  block_operator<book> book_finder;
public:
  BookManager();
  bool ISBN_find(string&ISBN,book&);
  bool name_find(string&name,std::vector<book>&);
  bool author_find(string&author,std::vector<book>&);
  bool keyword_find(string&keyword,std::vector<book>&);
  void show(Scanner&scanner);
  void buy(Scanner&scanner);
  void modify(Scanner&scanner);
  void import(Scanner&scanner);
};

#endif //BOOK_MANAGER_H
