#include "account_manager.hpp"
#include <cstring>
account_manager::account_manager() {
  store.initialize("account_head","account_body",max_account,min_account);
  account root("root","sjtu",7,"root");
  if(!store.find(root)) {
    store.insert(root);
  }
}
void account_manager::create(string &id, string &pd, int privilege, string &name) {
  account tmp(id,pd,privilege,name);
  store.insert(tmp);
}
bool account_manager::find(string &id) {
  account tmp{id};
  return store.find(tmp);
}
bool account_manager::find_and_get(string &id, account &t) {
  account tmp{id};
  if(store.find(tmp)) {
    t = tmp;
    return true;
  }
  return false;
}
void account_manager::Delete(string &id) {
  account tmp{id};
  store.Delete(tmp);
}
bool account_manager::find_and_check(string &id, string &pd, account &a) {
  account tmp{id};
  if(store.find(tmp)) {
    if(strlen(tmp.password) != pd.length()) {
      return false;
    }
    for(int i = 0;i < pd.length();i++) {
      if(tmp.password[i] != pd[i]) {
        return false;
      }
    }
    a = tmp;
    return true;
  }
  return false;
}
void account_manager::change_passwd(string &id, string &pd, string &new_pd) {
  account tmp;
  if(!find_and_check(id,pd,tmp)) {
    throw 0;
  }
  memset(tmp.password,0,30);
  for(int i = 0;i < new_pd.length();i++) {
    tmp.password[i] = new_pd[i];
  }
  store.update(tmp);
}
void account_manager::change_passwd(string &id, string &new_pd) {
  account tmp;
  if(!find_and_get(id,tmp)) {
    throw 0;
  }
  memset(tmp.password,0,30);
  for(int i = 0;i < new_pd.length();i++) {
    tmp.password[i] = new_pd[i];
  }
  store.update(tmp);
}

void account_manager::Register(string &id, string &pd, string &name) {
  account tmp(id,pd,1,name);
  if(store.find(tmp)) {
    throw 0;
  }
  store.insert(tmp);
}




