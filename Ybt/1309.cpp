#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

int base; // 进制
vector<int> v; // 高精度低位对应的下标小。 

vector<int> add(vector<int> a,vector<int> b)
{
	vector<int> c;
	if(a.size()<b.size()) swap(a,b);
	int t=0; // 存储进位。
	for(unsigned i=0;i<a.size();i++) {
		t=t+a[i];
		if(i<b.size()) t=t+b[i];
		c.push_back(t%base);
		t/=base;
	}
	if(t) c.push_back(t);
	return c;
}

bool isrev(vector<int> a)
{
	unsigned i;
	for(i=0;i<a.size();i++) 
		if(a[i]!=a[a.size()-i-1]) break;
	return (i==a.size());
}

int main()
{
	char ch;
	int step;
	cin>>base;
	while(cin>>ch) {
		if(ch>='0'&&ch<='9') 
			v.push_back(ch-'0');
		else v.push_back(ch-'A'+10);
	}
	reverse(v.begin(),v.end());
	vector<int> t;
	for(step=0;step<=30;step++) {
		if(isrev(v)) break;
		t=v; reverse(t.begin(),t.end());
		while((!t.back())&&t.size()>1) t.pop_back();
		v=add(v,t);
	}
	if(step<=30) printf("%d\n",step);
	else printf("Impossible\n");
	return 0;
}

