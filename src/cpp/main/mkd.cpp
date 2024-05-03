/*
生成测试数据，用来测试红黑树的查找插入删除
*/

#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
int arr[2000009];
int main()
{
	srand(time(nullptr));
    int n = 100000,m=100000;
	cout << n << " " << m << "\n";
	for(int i=0;i<n;++i) arr[i] = i+1;
	random_shuffle(arr,arr+n);
	for(int i=0;i<n;++i){
		cout << arr[i] << " " << "happy\n";
	}
	for(int i=1;i<=m;++i){
		int op=rand()%3+1;
		cout << op << " ";
		if(op==1){
			int x = rand()%(n*2);
			cout << x << "\n";
		}else if(op==2){
			int x = rand()%(n*3);
			cout << x << " ";
			cout << "happy\n";
		}else if(op==3){
			int x = rand()%(n*3);
			cout << x << "\n";
		}
	}
	return 0;
}