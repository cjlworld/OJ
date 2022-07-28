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

const int N=4e5+5;

struct Bits
{
	LL c[N];
	int n;
	inline int lowbit(int x) { return x&(-x); }
	inline void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	} 
	inline LL Sum(int x)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x))
			res+=c[x];
		return res;
	} 	
}C;

vector<int> vx,vy;

struct Station
{
	int x,y,p;
	inline bool operator<(const Station &t) const
	{
		return x<t.x;
	}
}a[N];

int getid(vector<int> &v,int x)
{
	return (upper_bound(v.begin(),v.end(),x)-v.begin());
}

struct Query
{
	int x,y;
	int id,sign;
	inline bool operator<(const Query &t) const
	{
		return x<t.x;
	}
	Query(int x,int y,int id,int sign) : x(x),y(y),id(id),sign(sign) {}
	Query() {}
}q[N];
int cnt;

inline void query(int x,int y,int id,int sign)
{
	q[++cnt]=Query(getid(vx,x),y=getid(vy,y),id,sign);
}

int n,m;
LL ans[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x1,y1,x2,y2;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].p);
	
	for(i=1;i<=n;i++) 
		vx.push_back(a[i].x),vy.push_back(a[i].y);
	sort(vx.begin(),vx.end());
	vx.erase(unique(vx.begin(),vx.end()),vx.end());
	sort(vy.begin(),vy.end());
	vy.erase(unique(vy.begin(),vy.end()),vy.end());
	for(i=1;i<=n;i++) {
		a[i].x=getid(vx,a[i].x);
		a[i].y=getid(vy,a[i].y);
	}
	
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		
		query(x2,y2,i,1);
		query(x1-1,y1-1,i,1);
		query(x2,y1-1,i,-1);
		query(x1-1,y2,i,-1);
	}
	
	sort(q+1,q+cnt+1);
	sort(a+1,a+n+1);
	
	C.n=vy.size();
	for(i=1,j=1;i<=cnt;i++) {
		for(;j<=n && a[j].x<=q[i].x;j++)
			C.Update(a[j].y,a[j].p);
		ans[q[i].id]+=C.Sum(q[i].y)*q[i].sign;
	} 
	
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

