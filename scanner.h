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
    string tmp;
    while(line[0] == ' ') {
      tmp += line[0];
      line.erase(0,1);
    }
    return tmp;
  }
};
#endif //SCANNER_H
