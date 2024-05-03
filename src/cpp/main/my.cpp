/*
基于本项目红黑树的map操作
*/

#include<bits/stdc++.h>
#include"RB_tree.h"
#define endl "\n"
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    _rbTree<int,string> RBT;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        string s;
        cin >> s;
        RBT.insert(make_pair(x,s));
        //RBT.debug();
    }
    for(int i=1;i<=m;++i){
        //RBT.debug();
        int op;
        cin >> op;
        if(op==1){
            int x;
            cin >> x;
            auto flag = RBT.find(x);
            if(flag==nullptr){
                //cout << "Not Found\n";
            }//else cout << flag->_val.first << " " << flag->_val.second << "\n";
        }else if(op==2){
            int x;
            string s;
            cin >> x;
            cin >> s;
            RBT.insert(make_pair(x,s));
        }else if(op==3){
            int x;
            cin >> x;
            if(RBT.find(x)!=nullptr){
                RBT.erase(x);
                //cout << "ERASE SUCCESS\n";
            }//else cout << "Not Found\n";
        }
    }
    return 0;
}
