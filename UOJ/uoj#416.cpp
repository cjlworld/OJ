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

int one[N],hs[N],idx;
int ver[N],Next[N];
inline void AddEdge(int h[],int a,int b)
{
	Next[idx]=h[a]; ver[idx]=b; h[a]=idx++;
	Next[idx]=h[b]; ver[idx]=a; h[b]=idx++;
	
//	printf("Edges(%d , %d)\n",a,b);
}

int dfn[N],low[N],times;
stack<int> S;
int cnt;

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) {
				cnt++;
				while(S.size() && S.top()!=y) {
					AddEdge(hs,S.top(),cnt);
					S.pop();
				}
				AddEdge(hs,y,cnt); S.pop();
				AddEdge(hs,x,cnt);
			}	
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

int n,m;
LL siz[N],Tsiz;

void Getsiz(int x,int fa)
{
	siz[x]=(x<=n);
	for(int i=hs[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Getsiz(y,x);
		siz[x]+=siz[y];
	}
}

LL ans;

void Dp(int x,int fa)
{
	int i,y;
	for(i=hs[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp(y,x);
	}
	
	LL sumsqr=0;
	for(i=hs[x];~i;i=Next[i]) 
		if(ver[i]!=fa) sumsqr+=siz[ver[i]]*siz[ver[i]];
	for(i=hs[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue; 
		
		if(x<=n) {
			ans+=(siz[x]-siz[y]-1)*siz[y]; // x -> c ; ytree -> s ; othertree in x -> f;
			ans+=2*(Tsiz-siz[x])*siz[y]; 
			// x -> c ; ytree -> s ; ancestor of x -> f;  
			// x -> c ; ancestor of x -> s; ytree -> f ; 
		}
		else {
			ans+=(siz[x]-siz[y])*siz[y]; // fa[x] -> c; 
			ans+=2*(Tsiz-siz[x])*(siz[x]-siz[y]); // tree -> c
			ans+=(siz[x]-siz[y])*(siz[x]-siz[y])-sumsqr+siz[y]*siz[y];
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(one,x,y);
	}
	
	memset(hs,-1,sizeof hs);
	cnt=n;
	for(i=1;i<=n;i++) 
		if(!dfn[i]) tarjan(i);
	
	for(i=1;i<=n;i++)
		if(!siz[i]) {
			Getsiz(i,-1);
			Tsiz=siz[i];
			Dp(i,-1);
		}
		
	printf("%lld\n",ans);
	return 0;
}

