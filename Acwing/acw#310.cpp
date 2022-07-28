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

const int N=256;
const LL INF=1e18;

int dim[N];
LL f[N][10][5][2]; 
// f[i][j][k][v] 表示在第i位上填j,同时紧接着前面（包括第i位）己经有k个6的情况的方案总数,已经有/没有 666. 

LL dfs(int now,int num,int k,int st,bool lt)
{
	if(now==1) return st;
	if(!lt&&f[now][num][k][st]!=-1) 
		return f[now][num][k][st];
	int maxn=((lt) ? dim[now-1] : 9);
	LL res=0;
	for(int i=0;i<=maxn;i++) {
		if(st) res+=dfs(now-1,i,0,1,lt&&i==maxn);
		else {
			if(i==6) {
				if(k==2) res+=dfs(now-1,i,0,1,lt&&i==maxn);
				else res+=dfs(now-1,i,k+1,st,lt&&i==maxn);
			}
			else res+=dfs(now-1,i,0,st,lt&&i==maxn);
		}
	}
	if(!lt) f[now][num][k][st]=res;
//	printf("%d %d %d %d : %lld\n",now,num,k,st,res);
	return res; 
}

LL count(LL n) // [1,n] 的魔鬼数有几个 
{
	memset(dim,0,sizeof dim);
	int top=0;
	while(n) dim[++top]=n%10,n/=10;
	LL res=0;
	for(int i=0;i<=dim[top];i++) 
		res+=dfs(top,i,i==6,0,i==dim[top]);
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	int T;
	LL x;
	LL L,R,mid;
	cin>>T;
	while(T--) {
		cin>>x;
		L=0,R=INF;
		while(L+1<R) { // (L,R]
			mid=(L+R)>>1; 
			if(count(mid)>=x) R=mid;
			else L=mid;
		}
		printf("%lld\n",R);
	}
	return 0;
}

