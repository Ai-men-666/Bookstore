#include "account.hpp"
#include <cstring>
account::account() {}
account::account(std::string id) {
  for(int i = 0;i < id.length();i++) {
    this->id[i] = id[i];
  }
}
account::account(std::string id, std::string pd, int privilege, std::string name) {
  for(int i = 0;i < id.length();i++) {
    this->id[i] = id[i];
  }
  for(int i = 0;i < pd.length();i++) {
    this->password[i] = pd[i];
  }
  for(int i = 0;i < name.length();i++) {
    this->name[i] = name[i];
  }
  this->privilege = privilege;
}

bool operator<(const account &a, const account &b) {
  for(int i = 0;i < 30;i++) {
    if(a.id[i] != b.id[i]) {
      return a.id[i] < b.id[i];
    }
  }
  return false;
}
bool operator<=(const account &a, const account &b) {
  for(int i = 0;i < 30;i++) {
    if(a.id[i] != b.id[i]) {
      return a.id[i] < b.id[i];
    }
  }
  return true;
}
bool operator>(const account &a,const account &b) {
  for(int i = 0;i < 30;i++) {
    if(a.id[i] != b.id[i]) {
      return a.id[i] > b.id[i];
    }
  }
  return false;
}
bool operator>=(const account &a, const account &b) {
  for(int i = 0;i < 30;i++) {
    if(a.id[i] != b.id[i]) {
      return a.id[i] > b.id[i];
    }
  }
  return true;
}
bool operator==(const account &a, const account &b) {
  for(int i = 0;i < 30;i++) {
    if(a.id[i] != b.id[i]) {
      return false;
    }
  }
  return true;
}
account &account::operator++() {
  for(int i = 29;i >= 0;i--) {
    if(id[i] != 0) {
      id[i]++;
      return *this;
    }
  }
  id[0]++;
  return *this;
}

