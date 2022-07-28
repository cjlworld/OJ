#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define LL long long 
using namespace std;
int n,m;
const int N=2e5+5; //kk????
int one[N];
LL ver[2*N],edge[2*N],Next[2*N];
int tot=0;
inline void add(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
LL dis[N];
int cnt[N];
bool vis[N];
struct cmp
{
	bool operator()(const int &a,const int &b)
	{
		return cnt[a]<cnt[b];
	}
};
priority_queue<int,vector<int>,cmp> q; //ÓÅ»¯ 
bool SPFA(int st)
{
	memset(dis,-1,sizeof(dis)); 
	memset(vis,0,sizeof(vis));
	while(q.size()) q.pop();
	dis[st]=0;
	vis[st]=true;
	cnt[st]++;
	q.push(st);
	int x,y;
	LL z;
	do {
		x=q.top(); q.pop();
		vis[x]=false;
		for(int i=one[x];i>0;i=Next[i])
		{
			y=ver[i]; z=edge[i];
			if(dis[x]+z>dis[y]) 
			{
				dis[y]=dis[x]+z;
				if(!vis[y]) {
					vis[y]=true;
					q.push(y);
					++cnt[y];
					if(cnt[y]>n+3) return false;
				}
			}
		}
	} while(q.size());
	return true;
}
LL ans;
int main()
{
//	freopen("1.in","r",stdin);
	int opt,x,y;
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&opt,&x,&y);
		switch(opt) {
			case 1 : add(x,y,0); add(y,x,0); break;
			case 2 : add(x,y,1); if(x==y) {puts("-1");return 0;}break;
			case 3 : add(y,x,0); break;
			case 4 : add(y,x,1); if(x==y) {puts("-1");return 0;}break;
			case 5 : add(x,y,0); break; //calc carefully
		}
	}
	for(i=1;i<=n;i++) add(0,i,1); //super start
	if(SPFA(0)==false) {
		puts("-1");
		return 0;
	}
	for(i=1;i<=n;i++)
		ans+=dis[i];
	printf("%lld\n",ans); //notice lld
	return 0;
}
