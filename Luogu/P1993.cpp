#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
int one[N],adj[N],edge[2*N],ver[2*N],Next[2*N];
int tot=0;
int dis[N],cnt[N];
bool exist[N],vis[N];
void add(int a,int b,int c)
{
	tot++;
	if(one[a]==-1) one[a]=tot;
	else Next[adj[a]]=tot;
	adj[a]=tot;
	edge[tot]=c;
	ver[tot]=b;
	return;
}
void Init()
{
	memset(one,-1,sizeof(one));
	memset(Next,-1,sizeof(Next));
	memset(adj,-1,sizeof(adj));
	scanf("%d%d",&n,&m);
	int kind,x,y,z;
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&kind,&x,&y);
		if(kind==3) {
			add(x,y,0);
			add(y,x,0);
		}
		else {
			scanf("%d",&z);
			if(kind==1) add(y,x,z);
			else add(x,y,-z);
		}
	}
	return;
}
//bool SPFA(int st)
//{
//	memset(dis,127,sizeof(dis));
//	memset(exist,false,sizeof(exist));
//	memset(cnt,0,sizeof(cnt));
//	while(!q.empty()) q.pop();
//	int u,v,l;
//	dis[st]=0; exist[st]=true; vis[st]=true;
//	q.push(st);
//	do {
//		u=q.front(); q.pop();
//		exist[u]=false; vis[u]=true;
//		for(int i=one[u];i!=-1;i=Next[i]) {
//			v=ver[i]; l=edge[i];
//			if(dis[u]+l<dis[v]) {
//				dis[v]=dis[u]+l;
//				cnt[v]++;
//				if(cnt[v]>n) return false;
//				if(!exist[v]) { q.push(v); exist[v]=true; }
//			}
//		}
//	} while(q.size());
//	return true;
//}
inline bool spfa(int u)
{
	exist[u]=true;
    vis[u]=true;
    for(int i=one[u];i!=-1;i=Next[i]) {
    	int v=ver[i],l=edge[i];
        if(dis[u]+l<dis[v]){
            dis[v]=dis[u]+l;
            if(vis[v]) return false;
            if(!spfa(v)) return false;
        }
	}
    vis[u]=false;
    return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	for(int i=1;i<=n;i++) {
		if(exist[i]) continue;
		if(!(spfa(i))) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}

