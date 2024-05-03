/*
基于RB_Tree实现的简易词典
提供插入<word, meaning>操作
提供基于关键字word的删除操作
提供基于关键字word的查找操作，返回迭代器
提供词典的合并操作
提供词典的数据可持久化(load && save)
*/

#include<bits/stdc++.h>
#include"RB_tree.h"
using namespace std;
class Dictionary{
public:
    void insert(const string &word, const string &meaning){_data.insert(word, meaning);}
    void erase(string &word){_data.erase(word);}
    Iterator<string,string> find(string &word) const{
        return Iterator<string,string>(_data.find(word));
    }
    Iterator<string,string> begin() const{return _data.begin();}
    Iterator<string,string> end() const{return _data.end();}
    size_t size() const{return _data.size();}
    void merge(Dictionary &dic){ //传入的字典将被清空并合并到this中
        while(dic.size()){
            auto p = dic._data.pop_root();
            insert(p.first,p.second);
        }
        cout << "合并结果：\n";
        _data.debug();
    }
    void clear(){
        while(size()){
            _data.pop_root();
        }
    }
private:
    _rbTree<string, string> _data;
};

void load(Dictionary &dic,const string &fileName){
    ifstream in(fileName,ios::in);
    vector<pair<string,string>>v;
    string word,meaning;
    while(in >> word && in >> meaning){
        v.push_back(make_pair(word,meaning));
    }
    dic.clear();
    for(auto p:v){
        dic.insert(p.first,p.second);
    }
    in.close();
}

void save(Dictionary &dic,const string &fileName){
    ofstream out(fileName,ios::out);
    for(auto it = dic.begin();it!=dic.end();++it){
        out << it->first << " " << it->second << "\n";
    }
    out.close();
}