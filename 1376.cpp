#include<bits/stdc++.h>
using namespace std;
priority_queue< pair<int,int> > q;
		//����ѣ����ȶ��У���pair�ĵڶ�άΪ�ڵ��ţ�
		//pair�ĵ�һάΪdis���෴���������෴�����С���ѣ�
		//Ĭ�϶�pair�ĵ�һά���� 
const int N=10000*2+5;
int dis[N];
bool exist[N];
int one[N],ver[N],edge[N],Next[N],adj[N];
int n,m;
int tot=0;
//http://ybt.ssoier.cn:8088/problem_show.php?pid=1381
/*����n, m����ʾ n�����к� m��·;
������m�У�ÿ��a b c����ʾ����a�����b�г���Ϊc��·��*/
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
		if(exist[x]) continue;//�Ѿ���ѡ�� 
		exist[x]=true;//ѡ��
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

