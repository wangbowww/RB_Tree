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
}dictionary1,dictionary2;

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

int main(){
    //字典合并
    cout << "合并：\n";
    load(dictionary1,"1.txt");
    cout << "dictionary1::\n";
    for(auto it = dictionary1.begin();it!=dictionary1.end();++it){
        cout << "[" << it->first << " " << it->second << "]\n";
    }
    cout << "\n";
    load(dictionary2,"2.txt");
    cout << "dictionary2::\n";
    for(auto it = dictionary2.begin();it!=dictionary2.end();++it){
        cout << "[" << it->first << " " << it->second << "]\n";
    }
    dictionary1.merge(dictionary2);
    cout << "\n";
	cout << "      英汉词典\n";
    cout << "      查看可用命令:help\n";
	while(1){
		cout << "\n";
        cout << "\n";
        string op;
        cin >> op;
        if(op[0]=='1'){
        	string word,meaning;
        	cin >> word >> meaning;
        	dictionary1.insert(word,meaning);
        	cout << "ok\n";
        }else if(op[0]=='2'){
        	string word;
        	cin >> word;
        	dictionary1.erase(word);
        	cout << "ok\n";
        }else if(op[0]=='3'){
        	string word;
        	cin >> word;
        	auto it = dictionary1.find(word);
        	if(it==nullptr){
        		cout << "Not Found\n";
        	}else{
        		cout << "[" << it->first << " " << it->second << "]\n";
        	}
        }else if(op[0]=='4'){
            for(auto it = dictionary1.begin();it!=dictionary1.end();++it){
                cout << "[" << it->first << " " << it->second << "]\n";
            }
        }else if(op=="help"){
            cout << "1 单词 汉语意思 (插入单词)\n";
            cout << "2 单词 (删除单词)\n";
            cout << "3 单词 (查询单词意思)\n";
            cout << "4 按照字典序显示字典中所有单词\n";
            cout << "load xxx.txt 从该文本文件中加载词典\n";
            cout << "save xxx.txt 从该文本文件中加载词典\n";
        }else if(op=="load"){
            string fileName;
            cin >> fileName;
            load(dictionary1,fileName);
            cout << "加载成功。\n";
        }else if(op=="save"){
            string fileName;
            cin >> fileName;
            save(dictionary1,fileName);
            cout << "保存成功。\n";
        }else{
        	cout << "命令格式错误。\n";
        }
	}
	return 0;
}