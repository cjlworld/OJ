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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=1e5+5,M=5e5+5;

int one[N],idx;
int ver[2*M],Next[2*M];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

int st[2*N][20];
int dfn[N],org[N],times;
int eu[2*N],fir[N],tot,w[N];
void dfs(int x,int fa)
{
	org[dfn[x]=++times]=x;
	eu[fir[x]=++tot]=dfn[x];
	w[x]=w[fa]+1;
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		eu[++tot]=dfn[x];
	}
}
int rmq(int x,int y)
{
	if(x>y) swap(x,y);
	int k=log2(y-x+1);
	return min(st[x][k],st[y-(1<<k)+1][k]);
}
int lca(int x,int y) { return org[rmq(fir[x],fir[y])]; }
int dist(int x,int y) { return w[x]+w[y]-2*w[lca(x,y)]; }

int n,m;
bool q[M]; 
int pre[N];
int cnt;

vector<int> t[M<<2];

#define lc (now<<1)
#define rc (now<<1|1)

void Modify(int now,int x,int y,int id,int l,int r)
{
	if(x<=l && r<=y) {
		t[now].push_back(id);
		cnt++;
		if(cnt>1e7) {
			cout<<cnt;
			exit(0);
		} 
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) Modify(lc,x,y,id,l,mid);
	if(y>=mid+1) Modify(rc,x,y,id,mid+1,r);
}

void dfs(int now,int l,int r,PII d)
{
	for(int i=0;i<(int)t[now].size();i++) {
		int u=t[now][i];
		if(!d.first) d.first=u;
		else if(!d.second) d.second=u;
		else {
			int fu=dist(d.first,u);
			int su=dist(d.second,u);
			int fs=dist(d.first,d.second);
			
			if(fu<su) swap(d.first,d.second); // ÈÃ d.second ½ÏÁÓ¡£
			if(fu>fs || su>fs) d.second=u; 
		}
	}
	
	if(l==r) {
		if(q[l]) {
			if(!d.first) puts("-1");
			else if(!d.second) puts("0");
			else printf("%d\n",dist(d.first,d.second));
		}
		return;
	}
	
	int mid=(l+r)>>1;
	dfs(lc,l,mid,d); dfs(rc,mid+1,r,d);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	char opt[2];
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	dfs(1,0);
	for(i=1;i<=tot;i++) st[i][0]=eu[i];
	for(j=1;(1<<j)<=tot;j++) 
		for(i=1;i+(1<<j)-1<=tot;i++) 
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	
	scanf("%d",&m);
	for(i=1;i<=n;i++) pre[i]=1;
	for(i=1;i<=m;i++) {
		scanf("%s",opt);
		if(*opt=='G') q[i]=true;
		else {
			scanf("%d",&x);
			if(!pre[x]) pre[x]=i;
			else {
				if(i>1) Modify(1,pre[x],i-1,x,1,m);
				pre[x]=0;
			}
		}
	}
	for(i=1;i<=n;i++) 
		if(pre[i]) Modify(1,pre[i],m,i,1,m); 
//	cout<<(sizeof(t)+sizeof(one)+sizeof(ver)+sizeof(Next)+
//		sizeof(q)+sizeof(pre)+sizeof(st)+sizeof(w)*6)/1024.0/1	024<<endl;
	dfs(1,1,m,PII(0,0));
	return 0;
}

