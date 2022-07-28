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

const int N=20,S=(1<<20);
const double _exp=1e-6;

inline bool equal(double x,double y) { return (x-y>-_exp&&x-y<_exp); }
struct Point
{
	double x,y;
}a[N];
struct Line
{
	double a,b;
	void init(Point s,Point k)
	{
		a=(k.y*s.x/k.x-s.y)/(s.x*k.x-s.x*s.x);
		b=(s.y-a*s.x*s.x)/s.x;
	}
	double f(double x) { return a*x*x+b*x; }
}l[N*N];
int tot;

int t[N*N],f[S];
int n,type,T;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&T);
	while(T--) {
		tot=0;
		scanf("%d%d",&n,&type);
		fill(f,f+(1<<n)+2,S);
		memset(t,0,sizeof t);
		for(i=0;i<n;i++) 
			scanf("%lf%lf",&a[i].x,&a[i].y);
		for(i=0;i<n;i++) 
			for(j=i+1;j<n;j++) {
				l[++tot].init(a[i],a[j]);
				if(l[tot].a>=0) tot--;
			}		
		
		for(i=1;i<=tot;i++) {
			for(j=0;j<n;j++) 
				if(equal(l[i].f(a[j].x),a[j].y)) 
					t[i]^=(1<<j);
			for(j=t[i];j;j=(j-1)&t[i]) f[j]=1;
		}
		for(i=0;i<n;i++) f[1<<i]=1;
		for(i=1;i<(1<<n);i++) 
			for(j=(i-1)&i;j;j=(j-1)&i) 
				f[i]=min(f[i],f[j]+f[i-j]);
		printf("%d\n",f[(1<<n)-1]);
	}
	return 0;
}

