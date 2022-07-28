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

vector<int> mul(vector<int> a,int b)
{
	vector<int> c;
	int t=0,i;
	for(i=0;i<(int)a.size();i++) {
		t=t+a[i]*b;
		c.push_back(t%10);
		t/=10;
	}
	while(t>0) {
		c.push_back(t%10);
		t/=10;
	}
	return c;
}

const int N=10010;

int p[N],tot=0;
bool tag[N];

void primes(int n)
{
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i;
		for(j=1;j<=tot && p[j]*i<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
	return;
}

int get(int n,int p)
{
	int cnt=0;
	for(int j=p;j<=n;j*=p) 
		cnt+=n/j;
	return cnt;
}

vector<int> C(int n,int m)
{
	int cnt;
	vector<int> c; c.push_back(1);
	for(int j=1;j<=tot && p[j]<=n;j++) {
		cnt=get(n,p[j])-get(m,p[j])-get(n-m,p[j]);
		while(cnt--) c=mul(c,p[j]);
	}
	return c;
}
int main()
{
//	freopen("1.in","r",stdin);
	
	int i,x,y;
	primes(N-1);
	cin>>x>>y;
	vector<int> ans=C(x,y);
	for(i=ans.size()-1;i>=0;i--) 
		printf("%d",ans[i]);
	
	return 0;
}

