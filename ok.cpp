#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    map<int,string>data;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        string s;
        cin >> s;
        data[x]=s;
    }
    for(int i=1;i<=m;++i){
        int op;
        cin >> op;
        if(op==1){        //查询
            int x;
            cin >> x;
            auto flag = data.find(x);
            if(flag==data.end()){
               // cout << "Not Found\n";
            }//else cout << flag->first << " " << flag->second << "\n";
        }else if(op==2){  //插入,成功返回Success!
            int x;
            cin >> x;
            string s;
            cin >> s;
            if(data.find(x)==data.end()){
                data[x] = s;
            }
        }else if(op==3){  //删除,不存在返回Not existed! / 成功返回Success!
            int x;
            cin >> x;
            if(data.find(x)!=data.end()){
                data.erase(x);
                //cout << "ERASE SUCCESS\n";
            }//else cout << "Not Found\n";
        }
    }
    return 0;
}
