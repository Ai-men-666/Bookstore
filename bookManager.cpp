#include <climits>
#include "book_manager.h"
#include "book.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ranges>

#include "entrystack.hpp"
#include "finance.h"
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
extern entry_stack stack;
bool cmp(book &a,book &b) {
  string stra(a.ISBN),strb(b.ISBN);
  return stra < strb;
}
extern char select_book[];
extern finance finance_recorder;
BookManager::BookManager() {
  ISBN_finder.initialize("ISBN_finder_head","ISBN_finder_body",ISBN_MAX,ISBN_MIN);
  name_finder.initialize("name_finder_head","name_finder_body",name_MAX,name_MIN);
  author_finder.initialize("author_finder_head","author_finder_body",author_MAX,author_MIN);
  key_word_finder.initialize("key_word_finder_head","key_word_finder_body",keyword_MAX,keyword_MIN);
  book_finder.initialize("book_finder_head","book_finder_body",book_MAX,book_MIN);
  book_finder.write_info(1,1);
}
int BookManager::get_book_id() {
  int a = 0;
  book_finder.get_info(a,1);
  return a;
}
void BookManager::add_book_id() {
  book_finder.write_info(get_book_id() + 1,1);
}

void BookManager::select(Scanner&scanner) {
  if(stack.cur_account().privilege < 3) {
    throw 0;
  }
  memset(select_book,0,20);
  string ISBN = scanner.next();
  for(int i = 0;i < ISBN.length();i++) {
    select_book[i] = ISBN[i];
  }
  book tmp;
  if(!ISBN_find(ISBN,tmp)) {
    book tmp_(ISBN);
    tmp_.id = get_book_id();
    add_book_id();
    book_finder.insert(tmp_);
    ISBN_to_id i(ISBN,tmp_.id);
    name_to_id n(tmp_.id);
    author_to_id a(tmp_.id);
    keyword_to_id k(tmp_.id);
    ISBN_finder.insert(i);
    name_finder.insert(n);
    author_finder.insert(a);
    key_word_finder.insert(k);
  }
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
  std::sort(res.begin(),res.end(),cmp);
  return true;
}
bool BookManager::author_find(string &author, std::vector<book> &res) {
  author_to_id tmp_author(author);
  std::vector<author_to_id> all_id;
  if(!author_finder.find_all(tmp_author,all_id)) {
    return false;
  }
  for(int i = 0;i < all_id.size();i++) {
    book tmp(all_id[i].id);
    book_finder.find(tmp);
    res.push_back(tmp);
  }
  std::sort(res.begin(),res.end(),cmp);
  return true;
}
bool BookManager::keyword_find(string &keyword, std::vector<book> &res) {
  keyword_to_id tmp_keyword(keyword);
  std::vector<keyword_to_id> all_id;
  if(!key_word_finder.find_all(tmp_keyword,all_id)) {
    return false;
  }
  for(int i = 0;i < all_id.size();i++) {
    book tmp(all_id[i].id);
    book_finder.find(tmp);
    res.push_back(tmp);
  }
  std::sort(res.begin(),res.end(),cmp);
  return true;
}
void BookManager::show(Scanner &scanner) {
  if(stack.cur_account().privilege < 1) {
    throw 0;
  }
  if(scanner.is_empty()) {
    std::vector<book> res;
    book_finder.list(res);
    std::sort(res.begin(),res.end(),cmp);
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
    return;
  }
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
    line.erase(0,1);
    line.erase(line.length() - 1,1);
    if(!name_find(line,res)) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
  }
  if(option == "-author") {
    line.erase(0,1);
    line.erase(line.length() - 1,1);
    if(!author_find(line,res)) {
      std::cout << '\n';
      return;
    }
    for(int i = 0;i < res.size();i++) {
      std::cout << res[i];
    }
  }
  if(option == "-keyword") {
    line.erase(0,1);
    line.erase(line.length() - 1,1);
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
  if(stack.cur_account().privilege < 1) {
    throw 0;
  }
  string ISBN = scanner.next();
  int quantity = to_int(scanner.next());
  book tmp;
  if(!ISBN_find(ISBN,tmp)) {
    throw 0;
  }
  if(tmp.quantity - quantity < 0 || quantity <= 0) {
    throw 0;
  }
  tmp.quantity -= quantity;
  std::cout << quantity * tmp.price << '\n';
  tmp.total_cost += quantity * tmp.price;
  book_finder.update(tmp);
  deal d{};
  d.income = quantity * tmp.price;
  finance_recorder.add_deal(d);
}
void BookManager::import(Scanner &scanner) {
  if(stack.cur_account().privilege < 3) {
    throw 0;
  }
  if(select_book[0] == -1) {
    throw 0;
  }
  int quantity = to_int(scanner.next());
  double total_cost = std::stod(scanner.next());
  if(total_cost < 0) {
    throw 0;
  }
  string ISBN(select_book);
  book tmp(ISBN);
  ISBN_find(ISBN,tmp);
  tmp.total_cost += total_cost;
  tmp.quantity += quantity;
  book_finder.update(tmp);
  deal d{};
  d.outcome = total_cost;
  finance_recorder.add_deal(d);
}
void BookManager::modify(Scanner &scanner) {
  if(stack.cur_account().privilege < 3) {
    throw 0;
  }
  if(select_book[0] == -1) {
    throw 0;
  }
  while(!scanner.is_empty()) {
    string line = scanner.next();
    string option = get_option(line);
    book tmp;
    if(option == "-ISBN") {
      string ISBN_old(select_book);
      ISBN_find(ISBN_old,tmp);
      memset(tmp.ISBN,0,20);
      if(ISBN_find(line,tmp)) {
        throw 0;
      }
      for(int i = 0;i < line.length();i++) {
        tmp.ISBN[i] = line[i];
      }
      ISBN_to_id new_ISBN(line,tmp.id);
      ISBN_to_id old_ISBN(ISBN_old,tmp.id);
      ISBN_finder.Delete(old_ISBN);
      ISBN_finder.insert(new_ISBN);
      book_finder.update(tmp);
      memset(select_book,0,20);
      for(int i = 0;i < line.length();i++) {
        select_book[i] = line[i];
      }
      continue;
    }
    if(option == "-name") {
      line.erase(0,1);
      line.erase(line.length() - 1,1);
      string ISBN_old(select_book);
      ISBN_find(ISBN_old,tmp);
      string old_name(tmp.name);
      name_to_id old_id(old_name,tmp.id);
      memset(tmp.name,0,60);
      for(int i = 0;i < line.length();i++) {
        tmp.name[i] = line[i];
      }
      name_to_id new_id(line,tmp.id);
      name_finder.Delete(old_id);
      name_finder.insert(new_id);
      book_finder.update(tmp);
      continue;
    }
    if(option == "-author") {
      line.erase(0,1);
      line.erase(line.length() - 1,1);
      string ISBN_old(select_book);
      ISBN_find(ISBN_old,tmp);
      string old_author(tmp.author);
      author_to_id old_id(old_author,tmp.id);
      memset(tmp.author,0,60);
      for(int i = 0;i < line.length();i++) {
        tmp.author[i] = line[i];
      }
      author_to_id new_id(line,tmp.id);
      author_finder.Delete(old_id);
      author_finder.insert(new_id);
      book_finder.update(tmp);
      continue;
    }
    if(option == "-keyword") {
      line.erase(0,1);
      line.erase(line.length() - 1,1);
      string ISBN_old(select_book);
      ISBN_find(ISBN_old,tmp);
      string old_keyword(tmp.keyword);
      memset(tmp.keyword,0,60);
      while(!old_keyword.empty()) {
        string keyword = get_keyword(old_keyword);
        keyword_to_id old(keyword,tmp.id);
        key_word_finder.Delete(old);
      }
      for(int i = 0;i < line.length();i++) {
        tmp.keyword[i] = line[i];
      }
      while(!line.empty()) {
        string keyword = get_keyword(line);
        keyword_to_id New(keyword,tmp.id);
        key_word_finder.insert(New);
      }
      book_finder.update(tmp);
      continue;
    }
    if(option == "-price") {
      double price = std::stod(line);
      string ISBN_old(select_book);
      ISBN_find(ISBN_old,tmp);
      tmp.price = price;
      book_finder.update(tmp);
      continue;
    }
    throw 0;
  }
}

