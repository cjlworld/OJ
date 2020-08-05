#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=2e5+5,M=4e5+5,INF=1e9+5,K=1e6+5;
int one[N];
int ver[M],Next[M],edge[M],idx=0;
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//=========================================
int n,k;
int ans=INF;
int Ts; // 当前处理的树的 size 
// 找到树的重心
// 树的重心的一个很重要的性质就是把其删去后,余下子树的size最大的最小 
int siz[N],mx[N]={INF}; // 子树的size，删去后的maxsize 
int Root;
bool vis[N];
void Gravity(int x,int fa)
{
	int i,y;
	siz[x]=1,mx[x]=0;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa||vis[y]) continue;
		Gravity(y,x);
		siz[x]+=siz[y];
		mx[x]=max(mx[x],siz[y]);
	}
	mx[x]=max(mx[x],Ts-siz[x]);
	if(mx[x]<mx[Root]) Root=x;
	return;
}
int w[K];
vector<int> v1,v2,del;
void Work(int x,int fa,int race,int dep)
{
	if(race>k) return;
	v1.push_back(race); v2.push_back(dep);
	for(int i=one[x];i>0;i=Next[i]) 
		if(ver[i]!=fa&&(!vis[ver[i]]))  
			Work(ver[i],x,race+edge[i],dep+1);
	return;
}
void Divide(int x)
{
	int i,j,y;
	vis[x]=true;
	w[0]=0;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(vis[y]) continue;
		v1.clear(); v2.clear();
		Work(y,x,edge[i],1);
		for(j=0;j<(int)v1.size();j++) ans=min(ans,v2[j]+w[k-v1[j]]);
		for(j=0;j<(int)v1.size();j++) w[v1[j]]=min(w[v1[j]],v2[j]),del.push_back(v1[j]);
	}
	for(i=0;i<(int)del.size();i++) w[del[i]]=INF;
	del.clear();
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(vis[y]) continue;
		Ts=siz[y];
		Root=0;
		Gravity(y,x);
		Divide(Root);
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++; y++;
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	memset(w,0x3f,sizeof w);
	Ts=n;
	vis[0]=true;
	Gravity(1,0);
	Divide(Root);
	if(ans==INF) cout<<"-1";
	else cout<<ans;
	return 0;
}

