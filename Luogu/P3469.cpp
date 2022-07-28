#include<stack>
#include<cstdio>
#include<cstring>
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
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>9) print(x/10);
	putchar(x%10+'0');
	return;
}
}
using FastIO::read;
using FastIO::print;
//=========================================
const int N=1e5+5;
const int M=5e5+5;
int one[N];
int Next[2*M],ver[2*M];
int tot=1;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//===========================================
LL n,m;
int dfn[N],low[N],times=0;
LL sum[N];
LL ans[N];
void tarjan(int now,const int &fa)
{
	dfn[now]=low[now]=++times;
	rint i,v;
	sum[now]=1;
	LL tmp=0;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(!dfn[v]) {
			tarjan(v,now);
			low[now]=min(low[now],low[v]);
			sum[now]+=sum[v];
			if(fa==-1) ans[now]+=sum[v]*(sum[v]-1);
			else if(low[v]>=dfn[now]) ans[now]+=sum[v]*(sum[v]-1),tmp+=sum[v];
		}
		else low[now]=min(low[now],dfn[v]);
	}
	if(fa!=-1) {
		tmp=n-tmp-1;
		ans[now]+=tmp*(tmp-1);
	}
	ans[now]=n*(n-1)-ans[now];
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	tarjan(1,-1);
	for(i=1;i<=n;i++) 
		print(ans[i]),putchar('\n');
	return 0;
}
