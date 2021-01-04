#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int n,m;

bool vis[N];
int siz[N];

int Getsiz(int x,int fa)
{
	int res=1,i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa||vis[y]) continue;
		res+=Getsiz(y,x);
	}
	return res;
}

void Gravity(int x,int fa,int Ts,int &Root)
{
	siz[x]=1;
	int i,y,ms=0;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]||y==fa) continue;
		Gravity(y,x,Ts,Root);
		ms=max(ms,siz[y]);
		siz[x]+=siz[y];
	}
	ms=max(ms,Ts-siz[x]);
	if(ms<=Ts/2) Root=x;
}

vector<int> vs,vc; // vson , vcur

void Work(int x,int fa,int dist)
{
	if(dist>m) return;
	vs.push_back(dist);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]||y==fa) continue;
		Work(y,x,dist+edge[i]);
	}
}

int Count(vector<int> &v)
{
	int i=0,j=v.size()-1,res=0;
	sort(v.begin(),v.end());
	for(;j>=0;j--) {
		for(;i<(int)v.size()&&v[i]+v[j]<=m;i++);
		res+=i;
	}
	for(i=v.size()-1;i>=0;i--) 
		if(v[i]*2<=m) res--;
	
//	for(j=v.size()-1;j>=0;j--) printf("%d ",v[j]);
//	printf(" : %d\n",res/2);
	return res/2;
}

int calc(int x)
{
	if(vis[x]) return 0;
	
	int i,j,y,res=0;
	Gravity(x,0,Getsiz(x,-1),x); // 找到当前节点所在树的重心 
	vis[x]=true; // 删除 
	
	vc.clear();
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]) continue;
		
		vs.clear();
		Work(y,x,edge[i]);
		res-=Count(vs);	
		for(j=vs.size()-1;j>=0;j--) vc.push_back(vs[j]);
		
	}
	res+=Count(vc);	
	for(j=vc.size()-1;j>=0;j--) 
		if(vc[j]<=m) res++;
		
	for(i=one[x];i;i=Next[i]) res+=calc(ver[i]);
	return res;
}


int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d",&n);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	scanf("%d",&m);
	
	printf("%d\n",calc(1));
	return 0;
}

