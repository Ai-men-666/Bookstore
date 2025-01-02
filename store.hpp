#ifndef STORE_HPP
#define STORE_HPP
#include <fstream>
#include <future>
#include <vector>
//块状链表
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
template<class T>
class nodeHead;
template<class T, int info_len = 2>
class MemoryRiver {
public:
    fstream file;
    string file_name;
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {
        file.open(file_name,std::ios::in|std::ios::out | std::ios::binary);
    }
    ~MemoryRiver() {
        file.close();
    }
    void open() {
        file.open(file_name,std::ios::in|std::ios::out | std::ios::binary);
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
    void ReadAll(T *all,int block_cnt) {
        file.seekg(8);
        file.read(reinterpret_cast<char *>(all), block_cnt * sizeof(T));
    }
    void UpdateAll(T *all,int block_cnt) {
        file.seekp(8);
        file.write(reinterpret_cast<char *>(all), block_cnt * sizeof(T));
    }
};
const int data_cnt_limit = 300;
const int data_max = 400;
template<class T>
class block {
public:
    T data[data_max]{};
    int data_cnt = 0;
};
template<class T>
class nodeHead {
public:
    nodeHead(T data_max,T data_min) :data_max(data_max),data_min(data_min){}
    nodeHead(){};
    T data_max{};
    T data_min{};
    int head_pos = 0;
    int block_pos = 0;
    int head_num = 0;
    int next_num = 0;
};
template<class T>
class block_operator {
public:
    void initialize(string head_name,string body_name,T data_max,T data_min) {
        head_memory_river.file_name = head_name;
        block_memory_river.file_name = body_name;
        head_memory_river.open();
        block_memory_river.open();
        ifstream h(head_name);
        ifstream b(body_name);
        if(!h) {
            head_memory_river.initialise(head_name);
            head_memory_river.write_info(2,1);
            nodeHead<T> begin(data_max,data_min);
            begin.head_pos = head_memory_river.write(begin);
            begin.head_num = 0;
            begin.next_num = 1;
            begin.block_pos = 8;
            nodeHead<T> end;
            end.head_pos = 8 + sizeof(nodeHead<T>);
            end.head_num = 1;
            begin.next_num = 1;
            head_memory_river.write(end);
            begin.next_num = end.head_num;
            head_memory_river.update(begin,8);
        }
        if(!b) {
            block_memory_river.initialise(body_name);
            block<T> begin;
            block_memory_river.write(begin);
        }
        head_memory_river.get_info(block_cnt,1);
        head_memory_river.ReadAll(all,block_cnt);
    }//初始化块状链表（输入表头，主体名，数据的最大最小值）
    block_operator(){}
    block_operator(string head_name,string body_name,T data_max,T data_min){
        head_memory_river.file_name = head_name;
        block_memory_river.file_name = body_name;
        head_memory_river.open();
        block_memory_river.open();
        ifstream h(head_name);
        ifstream b(body_name);
        if(!h) {
            head_memory_river.initialise(head_name);
            head_memory_river.write_info(2,1);
            nodeHead<T> begin(data_max,data_min);
            begin.head_pos = head_memory_river.write(begin);
            begin.head_num = 0;
            begin.block_pos = 8;
            nodeHead<T> end;
            end.head_pos = 8 + sizeof(nodeHead<T>);
            end.head_num = 1;
            begin.next_num = 1;
            head_memory_river.write(end);
            begin.next_num = end.head_num;
            head_memory_river.update(begin,8);
        }
        if(!b) {
            block_memory_river.initialise(body_name);
            block<T> begin;
            block_memory_river.write(begin);
        }
        head_memory_river.get_info(block_cnt,1);
        head_memory_river.ReadAll(all,block_cnt);
    }
    ~block_operator() {
        head_memory_river.UpdateAll(all,block_cnt);
        head_memory_river.write_info(block_cnt,1);
    }
    void insert(T &a) {
        int num = 0;
        while (num != 1) {
            if(all[num].data_max >= a && a >= all[num].data_min) {
                break;
            }
            num = all[num].next_num;
        }
        block<T> now;
        block_memory_river.read(now,all[num].block_pos);
        int l = 0,r = now.data_cnt;
        while(l < r) {
            int mid = (l + r) / 2;
            if(now.data[mid] < a) {
                l = mid + 1;
            }else {
                r = mid;
            }
        }
        if(now.data[l] == a) {
            return;
        }
        if(now.data[now.data_cnt - 1] < a) {
            now.data[now.data_cnt] = a;
        }else if(now.data[0] >= a) {
            for(int i = now.data_cnt - 1;i >= 0;--i) {
                now.data[i + 1] = now.data[i];
            }
            now.data[0] = a;
        }else {
            for(int i = now.data_cnt - 1;i >= l;--i) {
                now.data[i + 1] = now.data[i];
            }
            now.data[l] = a;
        }
        now.data_cnt++;
        if(now.data_cnt > data_cnt_limit) {
            block_cnt++;
            block<T> new_block;
            nodeHead<T> &next_head = all[all[num].next_num];
            nodeHead<T> &new_head = all[block_cnt - 1];
            for(int i = 0;i < data_cnt_limit / 2;++i) {
                std::swap(new_block.data[data_cnt_limit / 2 - 1 - i],now.data[now.data_cnt - 1 - i]);
            }
            new_block.data_cnt = data_cnt_limit / 2;
            now.data_cnt -= data_cnt_limit / 2;
            new_head.data_max = all[num].data_max;
            all[num].data_max = now.data[now.data_cnt - 1];
            T tmp = now.data[now.data_cnt - 1];
            new_head.data_min = ++tmp;
            new_head.block_pos = block_memory_river.write(new_block);
            new_head.head_num = block_cnt - 1;
            new_head.head_pos = sizeof(nodeHead<T>) * new_head.head_num + 8;
            all[num].next_num = new_head.head_num;
            new_head.next_num = next_head.head_num;
            block_memory_river.update(now,all[num].block_pos);
            all[new_head.head_num] = new_head;
        }else {
            block_memory_river.update(now,all[num].block_pos);
        }
    }//插入元素
    bool find(T &a) {
        int num = 0;
        T Max = all[num].data_max,Min = all[num].data_min;
        while(num != 1) {
            if(Max >= a && Min <= a) {
                break;
            }
            num = all[num].next_num;
            Max = all[num].data_max;
            Min = all[num].data_min;
        }
        int cnt = 0;
        block<T> now;
        block_memory_river.read(now,all[num].block_pos);
        while(Max >= a && Min <= a && num != 1) {
            if(now.data_cnt == 0) {
                num = all[num].next_num;
                block_memory_river.read(now,all[num].block_pos);
                continue;
            }
            int l = 0,r = now.data_cnt;
            while(l < r) {
                int mid = (l + r) / 2;
                if(now.data[mid] < a) {
                    l = mid + 1;
                }else {
                    r = mid;
                }
            }
            if(now.data[l] >= a && now.data[l] <= a) {
                a = now.data[l];
                return true;
            }
            num = all[num].next_num;
            block_memory_river.read(now,all[num].block_pos);
        }
        return false;
    }//找到返回true，并补全a
    void update(T &a) {
        Delete(a);
        insert(a);
    }//更新数据
    void Delete(T &a){
        int num = 0;
        while (num != 1) {
            if(all[num].data_max >= a && a >= all[num].data_min) {
                break;
            }
            num = all[num].next_num;
        }
        block<T> now;
        block_memory_river.read(now,all[num].block_pos);
        int l = 0,r = now.data_cnt;
        while(l < r) {
            int mid = (l + r) / 2;
            if(now.data[mid] < a) {
                l = mid + 1;
            }else {
                r = mid;
            }
        }
        if(now.data[l] == a) {
            T zero{};
            now.data[l] = zero;
            for(int i = l;i < now.data_cnt;++i) {
                now.data[i] = now.data[i + 1];
            }
            now.data_cnt--;
            block_memory_river.update(now,all[num].block_pos);
        }else {
            return;
        }
    }//删除数据
    bool find_all(T &a,std::vector<T> &res) {
        int num = 0;
        T Max = all[num].data_max,Min = all[num].data_min;
        while(num != 1) {
            if(Max >= a && Min <= a) {
                break;
            }
            num = all[num].next_num;
            Max = all[num].data_max;
            Min = all[num].data_min;
        }
        int cnt = 0;
        block<T> now;
        block_memory_river.read(now,all[num].block_pos);
        while(Max >= a && Min <= a && num != 1) {
            if(now.data_cnt == 0) {
                num = all[num].next_num;
                block_memory_river.read(now,all[num].block_pos);
                continue;
            }
            int l = 0,r = now.data_cnt;
            while(l < r) {
                int mid = (l + r) / 2;
                if(now.data[mid] < a) {
                    l = mid + 1;
                }else {
                    r = mid;
                }
            }
            while(now.data[l] >= a && now.data[l] <= a && l < now.data_cnt) {
                res.push_back(now.data[l++]);
                cnt++;
            }
            num = all[num].next_num;
            block_memory_river.read(now,all[num].block_pos);
        }
        if(cnt == 0) {
            return false;
        }
        return true;
    }//如果找到，返回true，将数据存在vector
    void write_info(int a,int pos) {
        block_memory_river.write_info(a,pos);
    }
    void get_info(int &a,int pos) {
        block_memory_river.get_info(a,pos);
    }
    void list(std::vector<T> &res) {
        int num = 0;
        while(num != 1) {
            block<T> now;
            block_memory_river.read(now,all[num].block_pos);
            for(int i = 0;i < now.data_cnt;i++) {
                res.push_back(now.data[i]);
            }
            num = all[num].next_num;
        }
    }//将所有数据存到res
private:
    int block_cnt = 0;
    MemoryRiver<block<T>> block_memory_river;
    MemoryRiver<nodeHead<T>> head_memory_river;
    nodeHead<T> all[6000]{};
};
#endif //STORE_HPP
