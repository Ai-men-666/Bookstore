#include "book.h"
#include <cstring>
#include <string>
bool operator < (book &a,book &b) {
  return a.id < b.id;
}
bool operator > (book &a,book &b) {
  return a.id > b.id;
}
bool operator >=(book &a,book &b) {
  return a.id >= b.id;
}
bool operator <=(book &a,book &b) {
  return a.id <= b.id;
}
bool operator ==(book &a,book &b) {
  return a.id == b.id;
}
book::book(int i) :id(i){}
book::book(){}
book::book(std::string&a) {
  for(int i = 0;i < a.length();i++) {
    ISBN[i] = a[i];
  }
}
ISBN_to_id::ISBN_to_id(std::string a) {
  for(int i = 0;i < a.length();i++) {
    ISBN[i] = a[i];
  }
}
std::ostream &operator<<(std::ostream &os, const book &a) {
  for(int i = 0;i < strlen(a.ISBN);i++) {
    os << a.ISBN[i];
  }
  os << '\t';
  for(int i = 0;i < strlen(a.name);i++) {
    os << a.name[i];
  }
  os << '\t';
  for(int i = 0;i < strlen(a.author);i++) {
    os << a.author[i];
  }
  os << '\t';
  for(int i = 0;i < strlen(a.keyword);i++) {
    os << a.keyword[i];
  }
  os << '\t';
  os << a.price << '\t' << a.quantity << '\n';
  return os;
}

ISBN_to_id::ISBN_to_id() {}
ISBN_to_id::ISBN_to_id(std::string &a, int id):ISBN_to_id(a) {
  this->id = id;
}

bool operator < (ISBN_to_id &a,ISBN_to_id &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra < strb;
}
bool operator > (ISBN_to_id &a,ISBN_to_id &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra > strb;
}
bool operator >=(ISBN_to_id &a,ISBN_to_id &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra >= strb;
}
bool operator <=(ISBN_to_id &a,ISBN_to_id &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra <= strb;
}
bool operator ==(ISBN_to_id &a,ISBN_to_id &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra == strb;
}
name_to_id::name_to_id(std::string a) {
  for(int i = 0;i < a.length();i++) {
    name[i] = a[i];
  }
}
name_to_id::name_to_id() {}
name_to_id::name_to_id(std::string &a, int id):name_to_id(a) {
  this->id = id;
}

bool operator < (name_to_id &a,name_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.name[i] != b.name[i]) {
      return a.name[i] < b.name[i];
    }
  }
  return false;
}
bool operator > (name_to_id &a,name_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.name[i] != b.name[i]) {
      return a.name[i] > b.name[i];
    }
  }
  return false;
}
bool operator >=(name_to_id &a,name_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.name[i] != b.name[i]) {
      return a.name[i] > b.name[i];
    }
  }
  return true;
}
bool operator <=(name_to_id &a,name_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.name[i] != b.name[i]) {
      return a.name[i] < b.name[i];
    }
  }
  return true;
}
bool operator ==(name_to_id &a,name_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.name[i] != b.name[i]) {
      return false;
    }
  }
  return true;
}
author_to_id::author_to_id(std::string a) {
  for(int i = 0;i < a.length();i++) {
    author[i] = a[i];
  }
}
author_to_id::author_to_id() {}
author_to_id::author_to_id(std::string &a, int id):author_to_id(a) {
  this->id = id;
}

bool operator < (author_to_id &a,author_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.author[i] != b.author[i]) {
      return a.author[i] < b.author[i];
    }
  }
  return false;
}
bool operator > (author_to_id &a,author_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.author[i] != b.author[i]) {
      return a.author[i] > b.author[i];
    }
  }
  return false;
}
bool operator >=(author_to_id &a,author_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.author[i] != b.author[i]) {
      return a.author[i] > b.author[i];
    }
  }
  return true;
}
bool operator <=(author_to_id &a,author_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.author[i] != b.author[i]) {
      return a.author[i] < b.author[i];
    }
  }
  return true;
}
bool operator ==(author_to_id &a,author_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.author[i] != b.author[i]) {
      return false;
    }
  }
  return true;
}
keyword_to_id::keyword_to_id(std::string a) {
  for(int i = 0;i < a.length();i++) {
    keyword[i] = a[i];
  }
}
keyword_to_id::keyword_to_id() {}
keyword_to_id::keyword_to_id(std::string &a, int id):keyword_to_id(a) {
  this->id = id;
}

bool operator < (keyword_to_id &a,keyword_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.keyword[i] != b.keyword[i]) {
      return a.keyword[i] < b.keyword[i];
    }
  }
  return false;
}
bool operator > (keyword_to_id &a,keyword_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.keyword[i] != b.keyword[i]) {
      return a.keyword[i] > b.keyword[i];
    }
  }
  return false;
}
bool operator >=(keyword_to_id &a,keyword_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.keyword[i] != b.keyword[i]) {
      return a.keyword[i] > b.keyword[i];
    }
  }
  return true;
}
bool operator <=(keyword_to_id &a,keyword_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.keyword[i] != b.keyword[i]) {
      return a.keyword[i] < b.keyword[i];
    }
  }
  return true;
}
bool operator ==(keyword_to_id &a,keyword_to_id &b) {
  for(int i = 0;i < 60;i++) {
    if(a.keyword[i] != b.keyword[i]) {
      return false;
    }
  }
  return true;
}
book &book::operator++() {
  id++;
  return *this;
}
ISBN_to_id &ISBN_to_id::operator++() {
  int i = 19;
  for(;i >= 0;i--) {
    if(ISBN[i] != 0) {
      break;
    }
  }
  ISBN[i]++;
  return *this;
}
name_to_id &name_to_id::operator++() {
  int i = 59;
  for(;i >= 0;i--) {
    if(name[i] != 0) {
      break;
    }
  }
  name[i]++;
  return *this;
}
author_to_id &author_to_id::operator++() {
  int i = 59;
  for(;i >= 0;i--) {
    if(author[i] != 0) {
      break;
    }
  }
  author[i]++;
  return *this;
}
keyword_to_id &keyword_to_id::operator++() {
  int i = 59;
  for(;i >= 0;i--) {
    if(keyword[i] != 0) {
      break;
    }
  }
  keyword[i]++;
  return *this;
}
ISBN_to_id::ISBN_to_id(int id) :id(id) {}
name_to_id::name_to_id(int id):id(id) {}
author_to_id::author_to_id(int id):id(id) {}
keyword_to_id::keyword_to_id(int id):id(id) {}