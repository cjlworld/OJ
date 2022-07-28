#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#define LL long long
using namespace std;
/*1<=N<=500,1<=M<=2500,1<=W<=200¡£(1<=F<=5)¸öÅ©³¡¡£*/
int t,n,m,h;
const int N=500+50;
int a[N][N],w[N][N];
int dis[N],vis[N],cnt[N];
bool exist[N];
queue<int> q;
inline void Init()
{
	memset(a,0,sizeof(a));
	memset(w,0x3f,sizeof(w));
	scanf("%d%d%d",&n,&m,&h);
	int x,y,z;
	for(int i=1;i<=m;i++) 
	{
		scanf("%d%d%d",&x,&y,&z);
		a[x][++a[x][0]]=y;
		a[y][++a[y][0]]=x;
		w[y][x]=w[x][y]=min(w[x][y],z);
	}
	for(int i=1;i<=h;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		a[x][++a[x][0]]=y;
		w[x][y]=min(w[x][y],-z);
	}
	return;
}
inline bool spfa(const int &st)
{
	memset(dis,127,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	while(q.size()) q.pop();
	
	exist[st]=true;
	dis[st]=0; vis[st]=true; cnt[st]++;
	q.push(st);
	int x,y,z;
	do {
		x=q.front(); q.pop();
		vis[x]=false;
		exist[x]=true;
		for(int i=1;i<=a[x][0];i++) 
		{
			y=a[x][i]; z=w[x][y];
			if(dis[x]+z<dis[y])
			{
				dis[y]=dis[x]+z;
				if(!vis[y]) 
				{
					q.push(y);
					vis[y]=true;
					cnt[y]++;
					if(cnt[y]>n) return true;
				}
			}
		}
	} while(q.size());
	return false;
}
inline bool Brain()
{
	memset(exist,0,sizeof(exist));
	for(int i=1;i<=n;i++) 
		if(!exist[i])
			if(spfa(i))
				return true;	
	return false;
}
int main()
{
	scanf("%d",&t);
	while(t--) 
	{
		Init();
		if(Brain()) puts("YES");
		else puts("NO");
	}
	return 0;
}

