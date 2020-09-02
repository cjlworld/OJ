#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,MOD=1e5+3,INF=0x3f3f3f3f;
int one[N],idx=1;
int Next[N],ver[N];
inline void AddEdge(int a,int b)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    return;
}
//==============================
int f[N];
queue<int> q;
int dis[N];
int n,m;
void bfs(int S)
{	
	int i,x,y;
	memset(dis,0x3f,sizeof dis);
	q.push(S); dis[S]=1,f[S]=1;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(dis[y]==INF) {
				dis[y]=dis[x]+1; 
				f[y]=(f[y]+f[x])%MOD;
				q.push(y);
			}
			else if(dis[x]+1==dis[y]) 
				f[y]=(f[y]+f[x])%MOD;
		}
	}
	return;
} 
int main()
{
//	freopen("1.in","r",stdin);
    int i,x,y;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++) {
    	scanf("%d%d",&x,&y);
    	AddEdge(x,y);
    	AddEdge(y,x);
	}
    bfs(1);
    for(i=1;i<=n;i++) 
    	printf("%d\n",f[i]);
    return 0;
}
//    for(i=1;i<=m;i++) {
//        scanf("%d%d%d",&x,&y,&z);
//        AddEdge(x,y,z);
//        AddEdge(y,x,z);
//    }
//    Dijstra(1);
//    topsort();
//    for(i=1;i<=n;i++) 
//        printf("%d\n",f[i]);
//priority_queue< pair<int,int> ,vector< pair<int,int> > , greater< pair<int,int> > > q;
//int dis[N];
//bool vis[N];
//int n,m;
//void Dijstra(int S)
//{
//    memset(dis,0x3f,sizeof dis);
//    memset(vis,0,sizeof vis);
//    int i,x,y,z;
//    q.push(make_pair(0,S)); dis[S]=0;
//    while(q.size()) {
//        x=q.top().second; q.pop();
//        if(vis[x]) continue;
//        vis[x]=true;
//        for(i=one[x];i>0;i=Next[i]) {
//            y=ver[i]; z=edge[i];
//            if(dis[y]>dis[x]+z) {
//                dis[y]=dis[x]+z;
//                q.push(make_pair(dis[y],y));
//            }
//        }
//    }
//    return;
//}
//void topsort()
//{
//    while(q.size()) q.pop();
//    q.push(make_pair(0,1));
//    int i,x,y,z;
//    f[1]=1;
//    memset(vis,0,sizeof vis);
//    while(q.size()) {
//        x=q.top().second; q.pop();
//        if(vis[x]) continue;
//        vis[x]=true;
//        for(i=one[x];i>0;i=Next[i]) {
//        	y=ver[i]; z=edge[i];
//        	if(dis[y]==dis[x]+z) {
//        		f[y]=(f[y]+f[x])%MOD;
//        		q.push(make_pair(dis[y],y));
//			}
//		}
//    }
//    return;
//}
