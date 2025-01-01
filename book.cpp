#include "book.h"
#include <cstring>
#include <string>
bool operator < (book &a,book &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra < strb;
}
bool operator > (book &a,book &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra > strb;
}
bool operator >=(book &a,book &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra >= strb;
}
bool operator <=(book &a,book &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra <= strb;
}
bool operator ==(book &a,book &b) {
  std::string stra(a.ISBN),strb(b.ISBN);
  return stra == strb;
}
book::book(int i) :id(i){}
book::book(){}
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
