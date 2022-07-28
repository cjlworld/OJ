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

const int N=2e5+5;
int one[N],idx=1;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

struct Trie
{
	int ch[32*N][2],idx;
	void insert(int x)
	{
		int i,s,now=0;
		for(i=31;i>=0;i--) {
			s=(x>>i)&1;
			if(!ch[now][s]) ch[now][s]=++idx;
			now=ch[now][s];
		}
	}
	int query(int x)
	{
		int i,s,now=0,res=0;
		for(i=31;i>=0;i--) {
			s=(x>>i)&1;
			if(ch[now][s^1]) now=ch[now][s^1],res^=(s^1)<<i;
			else now=ch[now][s],res^=s<<i;
		}
		return res;
	}
}T;

int w[N];
void dfs(int x,int fa)
{
	int i,y;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		w[y]=w[x]^edge[i];
		dfs(y,x);
	}
}

int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		AddEdge(x,y,z),AddEdge(y,x,z);
	} 
	dfs(1,0);
	int ans=0;
	T.insert(0);
	for(i=2;i<=n;i++) {
		ans=max(ans,w[i]^T.query(w[i]));
		T.insert(w[i]);
	}
	cout<<ans<<endl;
	return 0;
}

