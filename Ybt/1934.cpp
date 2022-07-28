#include<set>
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
set<int> S;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	cin>>n;
	for(i=1;i<=n;i++) {
		cin>>x;
		S.insert(x);
	}
	cout<<S.size()<<endl;
	for(set<int> :: iterator it=S.begin(); it!=S.end(); it++) 
		cout<<*it<<" ";
	return 0;
}

