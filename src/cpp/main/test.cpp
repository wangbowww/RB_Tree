#include<bits/stdc++.h>
#include"RB_tree.h"
using namespace std;

int main(){
	_rbTree<int,string> mp;
	for(int i=1;i<=5;++i){
        mp.insert(make_pair(i+3,"happy"));
    }
    string op;
    while(1){
        cin >> op;
        if(op=="insert"){
            int x;
            string a;
            cin >> x >> a;
            mp.insert(make_pair(x,a));
            cout << "ok for insert\n";
        }else if(op=="erase"){
            int x;
            cin >> x;
            mp.erase(x);
            cout << "ok for erase\n";
        }else if(op=="find"){
            int x;
            cin >> x;
            auto f = mp.find(x);
            if(f!=nullptr){
                cout << f->_val.first << " " << f->_val.second << endl;
            }else cout << "Not Found\n";
        }else if(op=="see"){
            mp.debug();
            cout << "ok for tree.dot\n";
        }
    }
	return 0;
}