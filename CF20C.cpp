#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N=1e5+5;
int n,m;
int one[N],adj[N],Next[N*2],ver[N*2];
LL edge[N*2];
int tot;
stack<int> ans;
LL dis[N];
bool exist[N];
int pre[N];
void add(int a,int b,LL c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
void Init()
{
    scanf("%d%d",&n,&m);
    int x,y;
	LL z;
    for(int i=1;i<=m;i++) {
		scanf("%d%d%lld",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
    }
    return;
}
priority_queue< pair<LL,int> > q;
void Dijkstra()
{
	memset(dis,127,sizeof(dis));
	memset(exist,0,sizeof(exist));
	while(q.size()) q.pop();
	int x,y;
	LL z;
	int i;
	dis[1]=0;
	q.push(make_pair(0,1));
	while(q.size()) {
		x=q.top().second; q.pop();
		if(exist[x]) continue;
		exist[x]=true;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[x]+z<dis[y]) {
				pre[y]=x;
				dis[y]=dis[x]+z;
				q.push(make_pair(-dis[y],y)); 
			}
		}
	}
	return;
}
int main()
{
	Init();
	Dijkstra();
	if(dis[n]==dis[0]) { puts("-1"); return 0; }
	int x=n;
	while(x)
	{
		ans.push(x);
		x=pre[x];
	}
	while(!ans.empty())
	{
		printf("%d ",ans.top());
		ans.pop();
	}
	return 0;
}
