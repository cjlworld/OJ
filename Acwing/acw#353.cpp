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

#define Debug fprintf(stderr, "Passed [%s] in LINE %d\n", __FUNCTION__, __LINE__)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5,INF=1e9+5;

int one[N],idx=1;
int ver[2*N],Next[2*N];
inline void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	return;
}

int n,m;
int st[3*N][31]; // st[j][i] = max { eu[j...j+2^i-1] }
int org[3*N],eu[3*N],dfn[N],fir[N],fat[N],times,tot;

void dfs(int x,int fa)
{
	int i,y;
	
	fat[x]=fa;
	dfn[x]=++times;
	org[times]=x;
	eu[++tot]=dfn[x];
	fir[x]=tot;
	
//	for(i=1;i<=tot;i++) printf("%d ",org[eu[i]]);
//	printf("\n");
	
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		eu[++tot]=dfn[x];
	}
	return;
}

int lca(int x,int y)
{
	x=fir[x]; y=fir[y];
//	Debug;
	if(x>y) swap(x,y);
	int k=(int)floor(log(y-x+1)/log(2));
	return org[min(st[x][k],st[y-(1<<k)+1][k])];
}

vector<int> v;
struct Require
{
	int x,y,z;
}q[N];

struct Node
{
	int lc,rc;
	int cmax;
}t[80*N];
int cnt;
int root[N];
void insert(int &now,int key,int val,int l,int r)
{
	if(!now) now=++cnt;
	if(l==r) {
		t[now].cmax+=val;
		return;
	}
	int mid=(l+r)>>1;
	if(key<=mid) insert(t[now].lc,key,val,l,mid);
	else insert(t[now].rc,key,val,mid+1,r);
	t[now].cmax=max(t[t[now].lc].cmax,t[t[now].rc].cmax);
	return;
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y) return x+y;
	if(l==r) {
		t[x].cmax+=t[y].cmax;
		return x;
	}
	int mid=(l+r)>>1;
	t[x].lc=merge(t[x].lc,t[y].lc,l,mid);
	t[x].rc=merge(t[x].rc,t[y].rc,mid+1,r);
	
	t[x].cmax=max(t[t[x].lc].cmax,t[t[x].rc].cmax); 
	return x;
}
int Fdmax(int now,int l,int r)
{
	if(!now) return 0;
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(t[t[now].lc].cmax==t[now].cmax) 
		return Fdmax(t[now].lc,l,mid);
	else return Fdmax(t[now].rc,mid+1,r);
}
//void Print(int now,int l,int r)
//{
//	if(l==r) {
//		for(int i=1;i<=t[now].cmax;i++) 
//			printf("%d ",v[l-1]);
//		return;
//	}
//	int mid=(l+r)>>1;
//	Print(t[now].lc,l,mid);
//	Print(t[now].rc,mid+1,r);
//	return;
//}
int ans[N];
void Recover(int x,int fa)
{
	int i,y;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Recover(y,x);
		root[x]=merge(root[x],root[y],1,v.size());
	}
//	printf("%d : ",x); Print(root[x],1,v.size()); printf("\n");
	if(t[root[x]].cmax==0) ans[x]=0;
	else ans[x]=Fdmax(root[x],1,v.size());
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	
	dfs(1,0);
//	for(i=1;i<=tot;i++) printf("%d ",org[eu[i]]);
//	printf("\n");	
//	for(i=1;i<=n;i++) printf("%d ",fir[i]);
//	printf("\n");
	for(i=1;i<=tot;i++) st[i][0]=eu[i];
	for(i=1;(1<<i)<=tot;i++) 
		for(j=1;j+(1<<i)-1<=tot;j++) 
			st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
	
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
		v.push_back(q[i].z);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=m;i++) 
		q[i].z=(int)(lower_bound(v.begin(),v.end(),q[i].z)-v.begin())+1;
//	Debug;
//	t[0].cmax=-INF;
	for(i=1;i<=m;i++) {
		z=lca(q[i].x,q[i].y);
		insert(root[q[i].x],q[i].z,1,1,v.size());
		insert(root[q[i].y],q[i].z,1,1,v.size());
		insert(root[z],q[i].z,-1,1,v.size());
		insert(root[fat[z]],q[i].z,-1,1,v.size());
		
//		printf("%d %d : %d\n",q[i].x,q[i].y,z);
	}
//	Debug;
	Recover(1,0);
//	Debug;
	for(i=1;i<=n;i++) {
		if(ans[i]==0) printf("0\n");
		else printf("%d\n",v[ans[i]-1]);
	}
		
	return 0;
}
/* DeBug : 
1.两次把 i 写成 x
2.min 写成 max
3.st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]); 的 (1<<i-1) 写成 (1<<i) 
4.忘记判掉一个物资也没有的情况。 
5.euler序的数组开小了 
6.org[] 开小了 
7.t[] 开小了 
*/
