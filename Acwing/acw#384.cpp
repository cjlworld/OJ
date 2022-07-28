#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int M=20+20;
const int N=1000+24;
const int dx[10]={0,1,-1};
int n,m;
LL c[M];
int vis[N][M];
LL dis[N][M];
struct data
{
	int floor;
	int con;
};
queue<data> q;
inline LL gabs(LL x)
{
	if(x>=0) return x;
	else return -x;
}
inline void SPFA()
{
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	int x,y,z;
	data u,v;
	int i,j;
	u.floor=1;
	for(i=1;i<=m;i++) 
		if(c[i]==0) {
			u.con=i;
			break;
		}
	dis[u.floor][u.con]=0;
	vis[u.floor][u.con]=true;
	q.push(u);
	
	do {
		u=q.front(); q.pop();
		vis[u.floor][u.con]=false;
		
		v.floor=u.floor+c[u.con];
		v.con=u.con;
		if(v.floor>=1&&v.floor<=n) {
			if(dis[u.floor][u.con]+abs(c[u.con])*2<dis[v.floor][v.con]) {
				dis[v.floor][v.con]=dis[u.floor][u.con]+gabs(c[u.con])*2;
				if(!vis[v.floor][v.con]) {
					q.push(v);
					vis[v.floor][v.con]=true;
				}
			}
		}
		v.floor=u.floor;
		for(i=1;i<=2;i++) {
			v.con=u.con+dx[i];
			if(v.con<1||v.con>m) continue;
			if(dis[u.floor][u.con]+1<dis[v.floor][v.con]) {
				dis[v.floor][v.con]=dis[u.floor][u.con]+1;
				if(!vis[v.floor][v.con]) {
					q.push(v);
					vis[v.floor][v.con]=true;
				}
			}
		}	
	} while(q.size());
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	int i,j;
	for(i=1;i<=m;i++) 	
		scanf("%lld",&c[i]);
	SPFA();
	LL ans=dis[0][0];
	for(i=1;i<=m;i++) 
		ans=min(ans,dis[n][i]);
	if(ans==dis[0][0]) 
		puts("-1");
	else 
		printf("%lld\n",ans);
	return 0;
}

