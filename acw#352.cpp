#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2e5+5;
int n,m;
struct Query
{
	int x,y;
	int o;	
	int ans;
	Query(int x,int y,int o) : x(x),y(y),o(o) {}
	Query() {}
}q[4*N];
int cnt=0;
struct Bits
{
	int c[N];
	inline int lowbit(int x) { return x&(-x); }
	inline void update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
		return;
	}
	inline int sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;
inline bool cmp(const Query &a,const Query &b)
{
	return a.x<b.x;
}
inline bool rule(const Query &a,const Query &b)
{
	return a.o<b.o;
}
//=========================================================
vector<int> v[N];

int dfn[N],dfnu[N],times=0;
void dfs(int x,int fa)
{
	int i,y;
	dfn[x]=++times;
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i];
		if(y==fa) continue;
		dfs(y,x);
	}
	dfnu[x]=times;
	return;
}
int a[N],s[N];
vector<int> cc[N];
int ans=0;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if(x==y) continue;
//		insert(1,dfn[x],dfn[y],1,n);
		a[dfn[x]]++; a[dfn[y]]++;
		cc[dfn[x]].push_back(dfn[y]);
	}
	for(i=1;i<=n;i++) {
		cnt++; q[cnt]=Query(dfnu[i],dfnu[i],cnt);
		cnt++; q[cnt]=Query(dfn[i]-1,dfn[i]-1,cnt);
		cnt++; q[cnt]=Query(dfnu[i],dfn[i]-1,cnt);
		cnt++; q[cnt]=Query(dfn[i]-1,dfnu[i],cnt);
	}
	sort(q+1,q+cnt+1,cmp);
	for(i=1;i<=cnt;i++) {
		for(j=q[i-1].x+1;j<=q[i].x;j++) {
			for(k=0;k<(int)cc[j].size();k++) 
				C.update(cc[j][k],1);
		}
		q[i].ans=C.sum(q[i].y);
	} 
	sort(q+1,q+cnt+1,rule);
	for(i=1;i<=n;i++) 
		s[i]=s[i-1]+a[i];
	for(x=2;x<=n;x++) {
		int tmp=s[dfnu[x]]-s[dfn[x]-1]-2*(q[4*(x-1)+1].ans+q[4*(x-1)+2].ans-q[4*(x-1)+3].ans-q[4*(x-1)+4].ans);
		if(tmp==0) ans+=m;
		else if(tmp==1) ans++;//,printf("%d %d\n",x,y);
	}
//	Dp(1,0);
	cout<<ans;
	return 0;
}
//vector<int> t[4*N];
//void insert(int now,int x,int y,int l,int r)
//{
//	t[now].insert(lower_bound(t[now].begin(),t[now].end(),y),y);
//	if(l==r) return;
//	int mid=(l+r)>>1;
//	if(x<=mid) insert(now<<1,x,y,l,mid);
//	else insert(now<<1|1,x,y,mid+1,r);
//	return; 
//}
//int query(int now,int x,int y,int k1,int k2,int l,int r)
//{
//	if(x<=l&&r<=y) 
//		return (int)(upper_bound(t[now].begin(),t[now].end(),k2)-lower_bound(t[now].begin(),t[now].end(),k1));
//	int mid=(l+r)>>1,res=0;
//	if(x<=mid) res+=query(now<<1,x,y,k1,k2,l,mid);
//	if(y>=mid+1) res+=query(now<<1|1,x,y,k1,k2,mid+1,r);
//	return res;
//}
//void Dp(int x,int fa)
//{
//	int i,y,tmp;
//	for(i=0;i<(int)v[x].size();i++) {
//		y=v[x][i];
//		if(y==fa) continue;
//		Dp(y,x);
//		tmp=get(y);
//		if(tmp==0) ans+=m;
//		else if(tmp==1) ans++;//,printf("%d %d\n",x,y);
////		printf("%d %d : %d\n",x,y,tmp);
//	}
//	return;
//}
//int get(int x)
//{
//	return 
//}
