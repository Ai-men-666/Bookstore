#ifndef SCANNER_H
#define SCANNER_H
#include <string>
using std::string;
class Scanner {
private:
  string line;
public:
  Scanner(string &line):line(line) {
    while (!line.empty() && line[0] == ' ') {
      line.erase(0,1);
    }
    while(!line.empty() && line[line.length()] == ' ') {
      line.erase(line.length() - 1,1);
    }
  }
  Scanner(){};
  void initialise(string &Line) {
    this->line.clear();
    this->line = Line;
    while (!line.empty() && line[0] == ' ') {
      line.erase(0,1);
    }
    while(!line.empty() && line[line.length()] == ' ') {
      line.erase(line.length() - 1,1);
    }
  }
  bool is_empty() {
    for(int i = 0;i < line.length();++i) {
      if(line[i] != ' ') {
        return false;
      }
    }
    return true;
  }
  string next() {
    if(is_empty()) {
      throw 0;
    }
    string tmp;
    while(line[0] == ' ') {
      line.erase(0,1);
    }
    while(line[0] != ' ' && !line.empty()) {
      tmp += line[0];
      line.erase(0,1);
    }
    return tmp;
  }
  string index_type() {
    string tmp;
    while (line[0] != '=' && !line.empty()) {
      tmp += line[0];
      line.erase(0,1);
    }
    return tmp;
  }
  /*string get_keyword() {

  }*/
};
inline int to_int(string a) {
  int sum = 0;
  for(int i = 0;i < a.length();i++) {
    if(a[i] < '0' || a[i] > '9') {
      throw 0;
    }
    sum = sum * 10 + a[i] - '0';
  }
  return sum;
}
inline string get_option(string&a) {
  string tmp;
  while(a[0] != '=' && a.length() > 0) {
    tmp += a[0];
    a.erase(0,1);
  }
  if(a[0] == '=') {
    a.erase(0,1);
  }
  return tmp;
}
inline string get_keyword(string &a) {
  string tmp;
  while(a[0] != '|' && !a.empty()) {
    tmp += a[0];
    a.erase(0,1);
  }
  if(a[0] == '|') {
    a.erase(0,1);
  }
  return tmp;
}
#endif //SCANNER_H
