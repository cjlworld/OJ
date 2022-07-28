#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

int K,B;
int f[36][12][31]; 
// f[now][top][sta] 表示 1 到第 now 位已经放了 sta 个 1 的方案数。
int dim[36];
LL dfs(int now,int top,int sta,bool lit)
{
	if(top>1) return 0;
	if(now==0) return (sta==0)&&(top==0);
	if(!lit&&f[now][top][sta]!=-1) 
		return f[now][top][sta];
	int maxn=(lit) ? dim[now-1] : B-1;
	LL res=0;
	for(int i=0;i<=maxn;i++) 
		res+=dfs(now-1,i,sta-(top==1),lit&&i==maxn);
	if(!lit) f[now][top][sta]=res;
	return res;
}
LL count(int n)
{
	memset(dim,0,sizeof dim);
	int top=0;
	while(n) dim[++top]=n%B,n/=B;
	LL res=0;
	for(int i=0;i<=dim[top];i++) 
		res+=dfs(top,i,K,i==dim[top]);
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int x,y;
	cin>>x>>y>>K>>B;
	memset(f,-1,sizeof f);
	cout<<count(y)-count(x-1);
	return 0;
}

