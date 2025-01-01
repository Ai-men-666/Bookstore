#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include <string>
class account {
public:
  int privilege = 0;
  char id[30]{};
  char password[30]{};
  char name[30]{};
  account();
  account(std::string id);
  account(std::string id,std::string pd,int privilege,std::string name );
  account& operator ++();
};
bool operator <(const account &a,const account &b);
bool operator <=(const account &a,const account &b);
bool operator >(const account &a,const account &b);
bool operator >=(const account &a,const account &b);
bool operator ==(const account &a,const account &b);
#endif //ACCOUNT_HPP
