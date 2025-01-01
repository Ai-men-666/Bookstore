#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <bits/posix2_lim.h>

class book {
public:
  int id = 0;
  char ISBN[20]{};
  char name[60]{},author[60]{};
  char keyword[60]{};
  int quantity = 0;
  double price = 0;
  double total_cost = 0;
  book(int);
  book();
  book(std::string&);
  book& operator++();
  friend std::ostream &operator<<(std::ostream &os,const book &a);
};
bool operator < (book &a,book &b);
bool operator > (book &a,book &b);
bool operator >=(book &a,book &b);
bool operator <=(book &a,book &b);
bool operator ==(book &a,book &b);

class ISBN_to_id {
public:
  char ISBN[20]{};
  int id = 0;
  ISBN_to_id(std::string);
  ISBN_to_id();
  ISBN_to_id(int);
  ISBN_to_id(std::string&,int);
  ISBN_to_id& operator++();
};
bool operator < (ISBN_to_id &a,ISBN_to_id &b);
bool operator > (ISBN_to_id &a,ISBN_to_id &b);
bool operator >=(ISBN_to_id &a,ISBN_to_id &b);
bool operator <=(ISBN_to_id &a,ISBN_to_id &b);
bool operator ==(ISBN_to_id &a,ISBN_to_id &b);
class name_to_id {
public:
  char name[60]{};
  int id = 0;
  name_to_id(std::string);
  name_to_id();
  name_to_id(int);
  name_to_id(std::string&,int);
  name_to_id& operator++();
};
bool operator < (name_to_id &a,name_to_id &b);
bool operator > (name_to_id &a,name_to_id &b);
bool operator >=(name_to_id &a,name_to_id &b);
bool operator <=(name_to_id &a,name_to_id &b);
bool operator ==(name_to_id &a,name_to_id &b);
class author_to_id {
public:
  char author[60]{};
  int id = 0;
  author_to_id(std::string);
  author_to_id();
  author_to_id(int);
  author_to_id(std::string&,int);
  author_to_id& operator++();
};
bool operator < (author_to_id &a,author_to_id &b);
bool operator > (author_to_id &a,author_to_id &b);
bool operator >=(author_to_id &a,author_to_id &b);
bool operator <=(author_to_id &a,author_to_id &b);
bool operator ==(author_to_id &a,author_to_id &b);
class keyword_to_id {
public:
  char keyword[60]{};
  int id = 0;
  keyword_to_id(std::string);
  keyword_to_id();
  keyword_to_id(std::string&,int);
  keyword_to_id(int);
  keyword_to_id& operator++();
};
bool operator < (keyword_to_id &a,keyword_to_id &b);
bool operator > (keyword_to_id &a,keyword_to_id &b);
bool operator >=(keyword_to_id &a,keyword_to_id &b);
bool operator <=(keyword_to_id &a,keyword_to_id &b);
bool operator ==(keyword_to_id &a,keyword_to_id &b);
#endif //BOOK_H
