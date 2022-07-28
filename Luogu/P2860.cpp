#include<set>
#include<stack>
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
//============================================
const int N=10000+5;
int one[N];
int Next[2*N],ver[2*N];
int tot=1;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//=============================================
int dfn[N],low[N],times=0;
stack<int> S;
int col[N],all=0;
int bridge[2*N];
void tarjan(int now,int fa)
{
	dfn[now]=low[now]=++times;
	S.push(now);
	rint i,v;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(!dfn[v]) {
			tarjan(v,now);
			low[now]=min(low[now],low[v]);
 		}
 		else if(ver[i]!=fa) //if(i!=(from^1)) 
 			low[now]=min(low[now],dfn[v]);
	}
	if(dfn[now]==low[now]) {
		all++;
		while(S.top()!=now) {
			col[S.top()]=all;
			S.pop();
		}
		col[now]=all;
		S.pop();
	}
	return;
}
int n,m;
set<int> E[N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x,y;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(i=1;i<=n;i++) 
		if(!dfn[i]) 
			tarjan(i,0);
	for(i=1;i<=n;i++) 
		for(j=one[i];j>0;j=Next[j]) {
			if(col[ver[j]]==col[i]) 
				continue;
			E[col[i]].insert(col[ver[j]]);
			E[col[ver[j]]].insert(col[i]);
		}
	int ans=0;
	for(i=1;i<=all;i++) 
		if(E[i].size()==1) 
			ans++;
	ans=(ans+1)>>1; 
	print(ans);
	return 0;
}


