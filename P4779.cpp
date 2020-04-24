#include<queue>
#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
#define rint register int
template<class T>
inline void read(T &x)
{
	x=0;
	register bool sign=false;
	register char c;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		sign= (c=='-') ? true : sign;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c-'0');
	x=(sign) ? ~x+1 : x;
	return;
}
const int N=5e5+5;
int one[N];
int ver[2*N],Next[2*N],edge[2*N];
int tot=0;
inline void AddEdge(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
int n,m,start;
int dis[N];
bool vis[N];
struct cmp
{
	inline bool operator()(const int &a,const int &b) 
	{
		return dis[a]>dis[b];	
	}	
};
priority_queue<int,vector<int>,cmp> q;
void SPFA(int st)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	rint i,j;
	rint x,y,z;
	dis[st]=0;
	vis[st]=true;
	q.push(st);
	while(q.size()) {
		x=q.top(); q.pop();
		vis[x]=false;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[x]+z<dis[y]) {
				dis[y]=dis[x]+z;
				if(!vis[y]) {
					q.push(y);
					vis[y]=true;
				}
			}
		} 
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	register int i,j;
	int x,y,z;
	read(n); read(m); read(start);
	for(i=1;i<=m;i++) {
		read(x); read(y); read(z);
		AddEdge(x,y,z);
	}
	SPFA(start);
	LL tmp=(1ll<<31ll)-1ll;
	for(i=1;i<=n;i++) {
		if(dis[i]==dis[0]) printf("%lld ",tmp);
		else printf("%d ",dis[i]);
	}
	return 0;
}

