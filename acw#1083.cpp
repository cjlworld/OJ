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

const int N=36;
int f[N][N];
int dim[N];
// f[now][num] 为 以 now 位为最高位且在 now 位填 num 的 windy 数的个数 
LL dfs(int now,int num,bool lt)
{
	if(now==1) return 1;
	if(!lt&&f[now][num]!=-1) 
		return f[now][num];
	int maxn=(lt) ? dim[now-1] : 9;
	LL res=0;
	for(int i=0;i<=maxn;i++) {
		if(abs(num-i)<2) continue;
		res+=dfs(now-1,i,lt&&i==maxn);
	}
	if(!lt) f[now][num]=res;
	return res;
}

LL count(int n)
{
	memset(dim,0,sizeof (dim));
	int tt=0;
	while(n) dim[++tt]=n%10,n/=10;
	
	LL res=0;
	for(int i=1;i<=dim[tt];i++) 
		res+=dfs(tt,i,i==dim[tt]);
	for(int i=tt-1;i>=1;i--) 
		for(int j=1;j<=9;j++) 
			res+=dfs(i,j,false);
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int a,b;
	memset(f,-1,sizeof f);
	cin>>a>>b;
	cout<<count(b)-count(a-1);
	return 0;
}

