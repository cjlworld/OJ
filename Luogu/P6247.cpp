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

const double eps=1e-12,PI=acos(-1),INF=1e18;

Vector rotate(Vector a,double b) { return Vector(a.x*cos(b)+a.y*sin(b),-a.x*sin(b)+a.y*cos(b)); }
Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
double length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }
double dist(Point a,Point b) { return length(a-b); }

const int N=1e5+5;
int n;
double cta;
Point a[N];

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i,j;
	
	cta=rand();
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%lf%lf",&a[i].x,&a[i].y);
		a[i]=rotate(a[i],cta);
	}
	
	sort(a+1,a+n+1);
	
	double cmin=INF,cmax=0;
	for(i=1;i<=n;i++) 
		for(j=i+1;j<=n && j<=i+6;j++) {
			cmin=min(cmin,dist(a[i],a[j]));
			cmax=max(cmax,dist(a[i],a[j]));
		}
	
	int T=min(n,10000000/n);
	for(i=1;i<=T;i++) 
		for(j=n;j>i;j--) {
			cmin=min(cmin,dist(a[i],a[j]));
			cmax=max(cmax,dist(a[i],a[j]));
		}
	
	printf("%.2lf %.2lf\n",cmin,cmax);
	return 0;
}

