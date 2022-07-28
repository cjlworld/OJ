#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define LL long long
using namespace std;
const LL H=1e9;
const int N=1e3+5;
int par[N];
LL w[N][N];
struct node
{
	LL x,y,z;
}a[N];
int n;
int T;
LL h,r,R;
//#define Area(x) ((double)(x*x))
inline LL Area(LL x) 
{
	return x*x;
}
LL dis(int x,int y)
{
//	return sqrt(Area(a[x].x-a[y].x)+Area(a[x].y-a[y].y)+Area(a[x].z-a[y].z));
	return Area(a[x].x-a[y].x)+Area(a[x].y-a[y].y)+Area(a[x].z-a[y].z);
}
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	return x;
}
inline void Join(int x,int y)
{
	int x_=Find(x);
	int y_=Find(y);
	if(x_==y_) return;
	par[x_]=y_;
	return;
}
inline void Init()
{
	memset(w,0,sizeof w);
	memset(a,0,sizeof a);
	memset(par,0,sizeof(par));
	for(int i=1;i<=N-1;i++) 
		par[i]=i;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d",&T);
	while(T--) {
		Init();
		scanf("%d%lld%lld",&n,&h,&r);
		R=4*Area(r);
		for(i=1;i<=n;i++) 
			scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].z);
		for(i=1;i<=n;i++) {
			for(j=i+1;j<=n;j++) {
				w[j][i]=w[i][j]=dis(i,j);
				if(w[i][j]<=R) Join(i,j);
			}
			if(a[i].z+r>=h) Join(1002,i);
			if(a[i].z-r<=0) Join(1003,i);
		}
		if(Find(1002)==Find(1003)) 
			puts("Yes");
		else puts("No");
	}
	return 0;
}

