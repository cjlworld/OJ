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
typedef pair<double,double> PDD;
typedef PDD Point;
typedef PDD Vector;

#define x first
#define y second

const double eps=1e-8,PI=acos(-1);

int sign(double x)
{
	if(fabs(x)<eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}

const int N=5000+5;

int n,m;
double up,down;
double u[N],d[N];
inline bool check(int b,Point a)
{
	if(!cmp(u[b],d[b])) return (a.x>u[b]);
	double k=(up-down)/(u[b]-d[b]);
	return (a.y < k * (a.x-d[b]) + down)^(k<0);
}

int binary(Point a)
{
	int L=0,R=n+1,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid,a)) L=mid;
		else R=mid;
	}
	return L;
}

int cnt[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	double x,y;
	bool is_first=true;
	while(scanf("%d",&n),n) {
		if(!is_first) printf("\n");
		is_first=false;
		
		memset(cnt,0,sizeof cnt);
		scanf("%d",&m);
		scanf("%lf%lf%lf%lf",&x,&up,&y,&down);
		
		for(i=1;i<=n;i++) 
			scanf("%lf%lf",&u[i],&d[i]);
		
		while(m--) {
			scanf("%lf%lf",&x,&y);
			cnt[binary(Point(x,y))]++;
		}
		
		for(i=0;i<=n;i++) 
			printf("%d: %d\n",i,cnt[i]);
	}
	return 0;
}

