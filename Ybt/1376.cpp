#include<bits/stdc++.h>
using namespace std;
priority_queue< pair<int,int> > q;
		//大根堆（优先队列），pair的第二维为节点编号；
		//pair的第一维为dis的相反数，利用相反数变成小根堆；
		//默认对pair的第一维排序； 
const int N=10000*2+5;
int dis[N];
bool exist[N];
int one[N],ver[N],edge[N],Next[N],adj[N];
int n,m;
int tot=0;
//http://ybt.ssoier.cn:8088/problem_show.php?pid=1381
/*输入n, m，表示 n个城市和 m条路;
接下来m行，每行a b c，表示城市a与城市b有长度为c的路。*/
void add(int a,int b,int c)//from a to b;
{
	tot++;
	if(one[a]==0) one[a]=tot;
	Next[adj[a]]=tot; adj[a]=tot;
	edge[tot]=c;
	ver[tot]=b;
	return;
}
void Init()
{
	int i,j;
	int a,b,c;
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	return;
}
void Dijkstra()
{
	memset(dis,127,sizeof(dis));
	memset(exist,0,sizeof(exist));
	int u,x,y,z;
	dis[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()) {
		x=q.top().second; q.pop();
		if(exist[x]) continue;//已经被选中 
		exist[x]=true;//选中
		for(int i=one[x];i;i=Next[i]) {//scan all the edges;
			y=ver[i]; z=edge[i];
			if(dis[y]>dis[x]+z) {  //improve node y;
				dis[y]=dis[x]+z;
				q.push(make_pair(-dis[y],y)); //push node y;
			}
		} 
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	Dijkstra();
	int ans=-1;
	for(int i=1;i<=n;i++) {
		if(dis[i]==dis[0]) {
			cout<<"-1";
			return 0;
		}
		ans=max(ans,dis[i]);
	}
	cout<<ans;
	return 0;
}

