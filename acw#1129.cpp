#include<bits/stdc++.h>
using namespace std;
priority_queue< pair<long long,int> > q;
		//大根堆（优先队列），pair的第二维为节点编号；
		//pair的第一维为dis的相反数，利用相反数变成小根堆；
		//默认对pair的第一维排序； 
const int N=2500+5;
const int M=10000*2+5;
#define end e_e
int dis[N];
bool exist[N];
int one[N],adj[N],ver[M],Next[M],edge[M];
int n,m;
int tot=0;
int st,end;
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
	cin>>st>>end;
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
	dis[st]=0;
	q.push(make_pair(0,st));
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
	cout<<dis[end];
	return 0;
}

