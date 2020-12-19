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

struct Bits
{
	map<int,LL> c[N];
	int n,m;
	inline int lowbit(int x) { return x&(-x); }
	
	inline void Update(int x,int y,int z)
	{
		for(;x<=n;x+=lowbit(x)) 
			for(int j=y;j<=m;j+=lowbit(j)) 
				c[x][j]+=z;
	} 
	inline LL Sum(int x,int y)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x))
			for(int j=y;j>=1;j-=lowbit(j))
				if(c[x].count(j))
					res+=c[x][j];
		return res;
	} 	
}C;

vector<int> vx,vy;

struct Station
{
	int x,y,p;
}a[N];

int getid(vector<int> &v,int x)
{
	return (upper_bound(v.begin(),v.end(),x)-v.begin());
}

inline LL query(int x,int y)
{
	x=getid(vx,x),y=getid(vy,y);
	return C.Sum(x,y);
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
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
	
	C.n=vx.size(),C.m=vy.size();
	for(i=1;i<=n;i++) {
		a[i].x=getid(vx,a[i].x);
		a[i].y=getid(vy,a[i].y);
		
		C.Update(a[i].x,a[i].y,a[i].p);
	}
	
	while(m--) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		printf("%lld\n",query(x2,y2)+query(x1-1,y1-1)-query(x2,y1-1)-query(x1-1,y2));
	}
	
	return 0;
}

