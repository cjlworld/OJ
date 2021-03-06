#include<set>
#include<stack>
#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
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
//===========================================
using namespace std;
const int N=100+5;
const int M=N*N+5;
int n;
struct Graph
{
	int one[N];
	int ver[M],Next[M];
	int tot;
	inline void AddEdge(const int &a,const int &b)
	{
		tot++;
		Next[tot]=one[a];
		one[a]=tot;
		ver[tot]=b;
		return;
	}
}GA,GB;
//==========================================
int dfn[N],low[N],times=0;
int col[N],all=0;
stack<int> S;
void tarjian(int now)
{
	dfn[now]=low[now]=++times;
	S.push(now);
	rint i,v;
	for(i=GA.one[now];i>0;i=GA.Next[i]) {
		v=GA.ver[i];
		if(!dfn[v]) {
			tarjian(v);
			low[now]=min(low[now],low[v]);
		}
		else if(col[v]==0) 
			low[now]=min(low[now],dfn[v]);
	}
	if(dfn[now]==low[now]) {
		all++;
		v=0;
		while(S.size()&&v!=now) {
			v=S.top(); S.pop();
			col[v]=all;
		}			
	}
	return;
}
set<int> Se[N];
int dep[N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x;
	read(n);
	for(i=1;i<=n;i++) {
		for(read(x);x!=0;read(x)) 
			GA.AddEdge(i,x);
	}
	for(i=1;i<=n;i++) 
		if(dfn[i]==0) 
			tarjian(i);
	for(i=1;i<=n;i++) 
		for(j=GA.one[i];j>0;j=GA.Next[j]) 
			if(col[i]!=col[GA.ver[j]]) 
				Se[col[i]].insert(col[GA.ver[j]]);
	for(i=1;i<=all;i++) {
		for(set<int>::iterator it=Se[i].begin();it!=Se[i].end();it++) 
			dep[*it]++;
	}
	int ans1=0,ans2=0;
	for(i=1;i<=all;i++) {
		if(dep[i]==0) ans1++;
		if(Se[i].size()==0) ans2++;
	}
	print(ans1),putchar('\n');
	print((all==1) ? 0 : max(ans1,ans2));
	return 0;
}

