#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
namespace FastIO
{
char c;
bool sign;
template<class T>
inline void read(T &x)
{
	x=0;
	sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c&15);
	if(sign) x=~x+1;
	return;
}
}
using FastIO::read;
//======================================
const int N=2e5+5;
const int M=1e6+5;
int one[N];
int ver[M],Next[M];
int tot=0;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//======================================
int n;
int a,b;
int dfn[N],low[N],times=0;
bool exa[N],exb[N]; // 在搜索树的子树中有没有 a，b
int ans=N+3;
void tarjan(int now,const int &fa)
{
	dfn[now]=low[now]=++times;
	rint i,v,child=0;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(!dfn[v]) {
			child++;
			tarjan(v,now);
			low[now]=min(low[now],low[v]);
			if(exa[v]) exa[now]=true;
			if(exb[v]) exb[now]=true; 
			if((fa==-1&&child>1)||(fa!=-1&&low[v]>=dfn[now]))
				if(exa[v]^exb[v]&&now!=a&&now!=b) // !!!
					ans=min(ans,now);
		}
		else if(v!=fa) 
			low[now]=min(low[now],dfn[v]);
	}
	return;
} 
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	read(n);
	while(true) {
		read(x); read(y);
		if(x==0&&y==0) 
			break;
		AddEdge(x,y);
		AddEdge(y,x);
	}
	read(a); read(b);
	exa[a]=true;
	exb[b]=true;
//	tarjan(a,-1);
	for(i=1;i<=n;i++) 
		if(dfn[i]==0) 
			tarjan(i,-1);
	if(ans==N+3) 
		puts("No solution");
	else printf("%d\n",ans);
	return 0;
}

