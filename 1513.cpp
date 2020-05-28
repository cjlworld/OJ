#include<set>
#include<stack>
#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
#define Gor(G,i,first) for(i=G.one[first];i>0;i=G.Next[i])
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
//===================================
const int N=1e4+5;
const int M=5e4+5;
struct graph
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
}GA;
//===================================
int dfn[N],low[N],times=0;
int color[N];
stack<int> S; 
int all=0;
void tarjian(int now)
{
	rint i,v;
	dfn[now]=low[now]=++times;
	S.push(now);
	Gor(GA,i,now) {
		v=GA.ver[i];
		if(dfn[v]==0) {
			tarjian(v);
			low[now]=min(low[now],low[v]);
		}
		else if(color[v]==0) 
			low[now]=min(low[now],dfn[v]);
	}
	if(dfn[now]==low[now]) {
		all++;
		v=0;
		while(v!=now&&S.size()) {
			v=S.top(); S.pop();
			color[v]=all;
		}
	}
	return;
}
int n,m;
set<int> se[N];
int dep[N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x,y;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		GA.AddEdge(x,y);
	}
	for(i=1;i<=n;i++) {
		if(dfn[i]==0) 
			tarjian(i);
	}
//	for(i=1;i<=n;i++) 
//		if(dfn[i]==0) {
//			printf("0\n");
//			return 0;
//		}
	for(i=1;i<=n;i++)
		Gor(GA,j,i) {
			if(color[GA.ver[j]]==color[i])
				continue;
			dep[color[i]]++;
		}
			
	int ans_co=0;
	int ans=0;
	for(i=1;i<=all;i++) {
		if(dep[i]==0&&ans_co==0)  
			ans_co=i;
		else if(dep[i]==0&&ans_co!=0) {
			puts("0");
			return 0;
		}
	}
	for(i=1;i<=n;i++) 
		if(color[i]==ans_co) 
			ans++;
	printf("%d\n",ans);
	return 0;
}

