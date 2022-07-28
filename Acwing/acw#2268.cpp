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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2e6+5;

int one[N],idx;
int ver[N],Next[N],edge[N];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
}


LL f[N];
LL ans;

void dfs(int x,int fa)
{
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		f[x]=max(f[x],f[y]+edge[i]);
	}
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		ans+=f[x]-f[y]-edge[i];
	}
}

int n,rt;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d%d",&n,&rt);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	
	dfs(rt,0);
	cout<<ans<<endl;
	return 0;
}

