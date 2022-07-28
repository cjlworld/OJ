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

const double eps=1e-8;
const int N=1000+5;

inline int dcmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}

struct Circle
{
	double x,y;
	double r;
}a[N];

int n;
PDD q[N];
inline double f(double x)
{
	int i;
	double y,len;
	int cnt=0;
	for(i=1;i<=n;i++) {
		len=fabs(a[i].x-x);
		if(dcmp(a[i].r,len)>0) {	
			y=sqrt(a[i].r*a[i].r-len*len);
			q[++cnt]=PDD(a[i].y-y,a[i].y+y);
		}
	}
	if(cnt==0) return 0;
	sort(q+1,q+cnt+1);
	double st=q[1].x,ed=q[1].y,res=0;
	for(i=2;i<=cnt;i++) {
		if(q[i].x<=ed) ed=max(ed,q[i].y);
		else {
			res+=ed-st;
			st=q[i].x,ed=q[i].y;
		}
	}
	res+=ed-st;
	return res;
}

inline double area(double l,double r)
{
	double mid=(l+r)/2;
	return (r-l)*(f(l)+4*f(mid)+f(r))/6;
}

double simpson(double l,double r,double s)
{
	double mid=(l+r)/2;
	double left=area(l,mid),right=area(mid,r);
	if(!dcmp(left+right,s)) return left+right;
	else return simpson(l,mid,left)+simpson(mid,r,right);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].r);
	printf("%.3lf\n",simpson(-2000,2000,area(-2000,2000)));
	return 0;
}

