#include <climits>
#include "book_manager.h"
#include "book.h"
#include <iostream>
#include <algorithm>
ISBN_to_id ISBN_MAX("~~~~~~~~~~~~~~~~~~~~");
ISBN_to_id ISBN_MIN{};
name_to_id name_MAX("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
name_to_id name_MIN{};
author_to_id author_MAX("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
author_to_id author_MIN{};
keyword_to_id keyword_MAX("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
keyword_to_id keyword_MIN{};
book book_MIN(-1);
book book_MAX(INT_MAX);
extern char select_book[];
BookManager::BookManager() {
  ISBN_finder.initialize("ISBN_finder_head","ISBN_finder_body",ISBN_MAX,ISBN_MIN);
  name_finder.initialize("name_finder_head","name_finder_body",name_MAX,name_MIN);
  author_finder.initialize("author_finder_head","author_finder_body",author_MAX,author_MIN);
  key_word_finder.initialize("key_word_finder_head","key_word_finder_body",keyword_MAX,keyword_MIN);
  book_finder.initialize("book_finder_head","book_finder_body",book_MAX,book_MIN);
}
bool BookManager::ISBN_find(string &ISBN, book &tmp) {
  ISBN_to_id tmp_ISBN(ISBN);
  if(!ISBN_finder.find(tmp_ISBN)) {
    return false;
  }
  tmp.id = tmp_ISBN.id;
  book_finder.find(tmp);
  return true;
}
bool BookManager::name_find(string &name, std::vector<book> &res) {
  name_to_id tmp_name(name);
  std::vector<name_to_id> all_id;
  if(!name_finder.find_all(tmp_name,all_id)) {
    return false;
  }
  for(int i = 0;i < all_id.size();i++) {
    book tmp(all_id[i].id);
    book_finder.find(tmp);
    res.push_back(tmp);
  }
  std::sort(res.begin(),res.end());
  return true;
}
bool BookManager::author_find(string &author, std::vector<book> &res) {
  author_to_id tmp_author(author);
  std::vector<author_to_id> all_id;
  if(!author_finder.find(tmp_author)) {
    return false;
  }
  for(int i = 0;i < all_id.size();i++) {
    book tmp(all_id[i].id);
    book_finder.find(tmp);
    res.push_back(tmp);
  }
  std::sort(res.begin(),res.end());
  return true;
}
bool BookManager::keyword_find(string &keyword, std::vector<book> &res) {
  keyword_to_id tmp_keyword(keyword);
  std::vector<keyword_to_id> all_id;
  if(!key_word_finder.find(tmp_keyword)) {
    return false;
  }
  for(int i = 0;i < all_id.size();i++) {
    book tmp(all_id[i].id);
    book_finder.find(tmp);
    res.push_back(tmp);
  }
  std::sort(res.begin(),res.end());
  return true;
}
void BookManager::show(Scanner &scanner) {
  string line = scanner.next();
  string option = get_option(line);
  book tmp;
  std::vector<book> res;
  if(option == "-ISBN") {
    if(!ISBN_find(line,tmp)) {
      std::cout << '\n';
      return;
    }
    std::cout << tmp;
  }
  if(option == "-name") {
    if(!name_find(line,res)) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
  }
  if(option == "-author") {
    if(!author_find(line,res)) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
  }
  if(option == "-keyword") {
    if(!keyword_find(line,res)) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
  }
}

void BookManager::buy(Scanner &scanner) {
  string ISBN = scanner.next();
  int quantity = to_int(scanner.next());
  book tmp;
  if(!ISBN_find(ISBN,tmp)) {
    throw 0;
  }
  tmp.quantity -= quantity;
  if(tmp.quantity < 0 || quantity <= 0) {
    throw 0;
  }
  std::cout << quantity * tmp.price;
  book_finder.update(tmp);
}
void BookManager::import(Scanner &scanner) {
  if(select_book[0] == -1) {
    throw 0;
  }
  int quantity = to_int(scanner.next());
  double total_cost = std::stod(scanner.next());
  if(total_cost < 0) {
    throw 0;
  }
  string ISBN(select_book);
  book tmp;
  if(ISBN_find(ISBN,tmp)) {
    tmp.total_cost += total_cost;



  }
}

