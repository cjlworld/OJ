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

const int N=2048,M=2e4+5;

int one[N],idx=1;
int Next[M],ver[M];
inline void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	return;
}

int f[N];

int SG(int x)
{
	if(f[x]!=-1) return f[x];
	int i,y;
	set<int> S;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		S.insert(SG(y));
	} 
	for(i=0;;i++) 
		if(!S.count(i)) {
			f[x]=i;
			break;
		}
	return f[x];
}

int n,m,k;
int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	
	int i,x,y,ans=0;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}

	for(i=1;i<=k;i++) {
		scanf("%d",&x);
		ans^=SG(x);
	}
	if(ans>0) printf("win");
	else printf("lose");
	return 0;
}

