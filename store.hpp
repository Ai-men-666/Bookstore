#ifndef STORE_HPP
#define STORE_HPP
#include <iostream>
#include <fstream>
#include <bit>
#include <future>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

class nodeHead;
const int sizeof_nodeHead = 160;
template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    string file_name;
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {
        file.open(file_name,std::ios::in|std::ios::out | std::ios::binary);
    }
    ~MemoryRiver() {
        file.close();
    }

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
        file.open(file_name,std::ios::in|std::ios::out | std::ios::binary);
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        file.seekg(sizeof(int)*(n-1));
        file.read(reinterpret_cast<char *>(&tmp), sizeof(int));
        /* your code here */
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        file.seekp(sizeof(int)*(n-1));
        file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        /* your code here */
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        file.seekp(0,std::ios::end);
        std::streampos index = file.tellp();
        file.write(reinterpret_cast<char*>(&t), sizeof(T));
        int position_index = static_cast<int>(index);
        return position_index;
        /* your code here */
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        file.seekp(index );
        file.write(reinterpret_cast<char*>(&t), sizeof(T));
        /* your code here */
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        file.seekg(index );
        file.read(reinterpret_cast<char*>(&t), sizeof(T));
        /* your code here */
    }
    void Read(nodeHead *all,int block_cnt) {
        file.seekg(8);
        file.read(reinterpret_cast<char *>(all), block_cnt * sizeof_nodeHead);
    }
    void Update(nodeHead *all,int block_cnt) {
        file.seekp(8);
        file.write(reinterpret_cast<char *>(all), block_cnt * sizeof_nodeHead);
    }
};

const int data_cnt_limit = 300;
const int data_max = 400;
int block_cnt;
struct Data {
    Data(string index,int value) {
        for(int i = 0;i < index.length();i++) {
            this->index[i] = index[i];
        }
        this->value = value;
    }
    bool operator==(const Data &other) const {
        if(value != other.value) {
            return false;
        }
        for(int i = 0;i < 65;++i) {
            if(index[i] != other.index[i]) {
                return false;
            }
        }
        return true;
    }
    void initialise() {
        for(int i = 0;i < 65;++i) {
            index[i] = 0;
        }
        value = 0;
    }
    Data(){};
    char index[65]{};
    int value = 0;
};
class nodeHead {
public:
    nodeHead() {
        for(int i = 0;i < 65;i++) {
            data_max.index[i] = 1;
            data_min.index[i] = 0;
        }
    }
    Data data_max;
    Data data_min;
    int head_pos = 0;
    int block_pos = 0;
    int head_num = 0;
    int next_num = 0;
}all[6000]{};


class block {
public:
    Data data[data_max]{};
    int data_cnt = 0;
};
bool cmp_index(string &a,string &b) {
    if(a.length() != b.length()) {
        return a.length() > b.length();
    }
    for(int i = 0;i < a.length();i++) {
        if(a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
    return true;
}//大于等于返回true
bool cmp_index(char *a,char *b) {
    string sa = a,sb = b;
    if(sa.length() != sb.length()) {
        return sa.length() > sb.length();
    }
    for(int i = 0;i < sa.length();i++) {
        if(a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
    return true;
}//大于等于返回true
bool cmp_data(Data &a,Data &b) {
    string sa = a.index,sb = b.index;
    if(sa.length() != sb.length()) {
        return sa.length() > sb.length();
    }
    for(int i = 0;i < sa.length();i++) {
        if(sa[i] != sb[i]) {
            return sa[i] > sb[i];
        }
    }
    if(a.value != b.value) {
        return a.value > b.value;
    }
    return true;
}//大于等于返回true

void insert(MemoryRiver<block> &block_memory_river,
  string &index,int value) {
    int num = 0;
    Data target(index,value);
    while (num != 1) {
        if(cmp_data(all[num].data_max,target) && cmp_data(target,all[num].data_min)) {
            break;
        }
        num = all[num].next_num;
    }
    block now;
    block_memory_river.read(now,all[num].block_pos);
    int l = 0,r = now.data_cnt;
    while(l < r) {
        int mid = (l + r) / 2;
        if(!cmp_data(now.data[mid],target)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    if(now.data[l] == target) {
        return;
    }
    if(!cmp_data(now.data[now.data_cnt - 1],target)) {
        now.data[now.data_cnt] = target;
    }else if(cmp_data(now.data[0],target)) {
        for(int i = now.data_cnt - 1;i >= 0;--i) {
            now.data[i + 1] = now.data[i];
        }
        now.data[0] = target;
    }else {
        for(int i = now.data_cnt - 1;i >= l;--i) {
            now.data[i + 1] = now.data[i];
        }
        now.data[l] = target;
    }
    now.data_cnt++;
    if(now.data_cnt > data_cnt_limit) {
        block_cnt++;
        block new_block;
        nodeHead &next_head = all[all[num].next_num];
        nodeHead &new_head = all[block_cnt - 1];
        for(int i = 0;i < data_cnt_limit / 2;++i) {
            std::swap(new_block.data[data_cnt_limit / 2 - 1 - i],now.data[now.data_cnt - 1 - i]);
        }
        new_block.data_cnt = data_cnt_limit / 2;
        now.data_cnt -= data_cnt_limit / 2;
        new_head.data_max = all[num].data_max;
        all[num].data_max = now.data[now.data_cnt - 1];
        new_head.data_min = now.data[now.data_cnt - 1];
        new_head.data_min.value++;
        new_head.block_pos = block_memory_river.write(new_block);
        new_head.head_num = block_cnt - 1;
        new_head.head_pos = sizeof_nodeHead * new_head.head_num + 8;
        all[num].next_num = new_head.head_num;
        new_head.next_num = next_head.head_num;
        block_memory_river.update(now,all[num].block_pos);
        all[new_head.head_num] = new_head;
    }else {
        block_memory_river.update(now,all[num].block_pos);
    }
}

void Delete(MemoryRiver<block> &block_memory_river,
  string &index,int value) {
    int num = 0;
    Data target(index,value);
    while (num != 1) {
        if(cmp_data(all[num].data_max,target) && cmp_data(target,all[num].data_min)) {
            break;
        }
        num = all[num].next_num;
    }
    block now;
    block_memory_river.read(now,all[num].block_pos);
    int l = 0,r = now.data_cnt;
    while(l < r) {
        int mid = (l + r) / 2;
        if(!cmp_data(now.data[mid],target)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    if(now.data[l] == target) {
        now.data[l].initialise();
        for(int i = l;i < now.data_cnt;++i) {
            now.data[i] = now.data[i + 1];
        }
        now.data_cnt--;
        block_memory_river.update(now,all[num].block_pos);
    }else {
        return;
    }
}
int find_cnt = 0;
void find(MemoryRiver<block> &block_memory_river,
  string &index) {
    find_cnt++;
    if(find_cnt == 114) {
        find_cnt = 114;
    }
    int num = 0;
    Data target(index,0);
    char *Max = all[num].data_max.index,*Min = all[num].data_min.index;
    while(num != 1) {
        if(cmp_index(Max,&index[0]) && cmp_index(&index[0],Min)) {
            break;
        }
        num = all[num].next_num;
        Max = all[num].data_max.index;
        Min = all[num].data_min.index;
    }
    int cnt = 0;
    block now;
    block_memory_river.read(now,all[num].block_pos);
    while(cmp_index(Max,&index[0]) && cmp_index(&index[0],Min) && num != 1) {
        if(now.data_cnt == 0) {
            num = all[num].next_num;
            block_memory_river.read(now,all[num].block_pos);
            continue;
        }
        int l = 0,r = now.data_cnt;
        while(l < r) {
            int mid = (l + r) / 2;
            if(!cmp_data(now.data[mid],target)) {
                l = mid + 1;
            }else {
                r = mid;
            }
        }
        string l_string = now.data[l].index;
        string t = target.index;
        /*if(l_string != t) {
            if(cnt == 0) {
                std::cout << "null\n";
                return;
            }
            std::cout << '\n';
            return;
        }*/
        while(l_string == t && l < now.data_cnt) {
            std::cout << now.data[l++].value << ' ' ;
            l_string = now.data[l].index;
            cnt++;
        }
        num = all[num].next_num;
        block_memory_river.read(now,all[num].block_pos);
    }
    if(cnt == 0) {
        std::cout << "null";
    }
    std::cout << '\n';
}
int main()
{
    int n;
    std::cin >> n;
    std::string order;
    MemoryRiver<nodeHead> head_memory_river("head");
    MemoryRiver<block> block_memory_river("block");
    ifstream h("head");
    ifstream b("block");
    if(!h) {
        head_memory_river.initialise("head");
        head_memory_river.write_info(2,1);
        nodeHead begin;
        begin.head_pos = head_memory_river.write(begin);
        begin.head_num = 0;
        begin.block_pos = 8;
        nodeHead end;
        end.head_pos = 168;
        end.head_num = 1;
        head_memory_river.write(end);
        begin.next_num = end.head_num;
        head_memory_river.update(begin,8);
    }
    if(!b) {
        block_memory_river.initialise("block");
        block begin;
        block_memory_river.write(begin);
    }
    head_memory_river.get_info(block_cnt,1);
    head_memory_river.Read(all,block_cnt);
    head_memory_river.get_info(block_cnt,1);
    head_memory_river.Read(all,block_cnt);
    for(int i = 0;i < n;++i) {
        std::cin >> order;
        if(order == "insert") {
            int value;
            string index;
            std::cin >> index >> value;
            insert(block_memory_river,index,value);
        }
        if(order == "delete") {
            int value;
            string index;
            std::cin >> index >> value;
            Delete(block_memory_river,index,value);
        }
        if(order == "find") {
            string index;
            std::cin >> index;
            find(block_memory_river,index);
        }
    }
    head_memory_river.write_info(block_cnt,1);
    head_memory_river.Update(all,block_cnt);
    return 0;
}

#endif //STORE_HPP
