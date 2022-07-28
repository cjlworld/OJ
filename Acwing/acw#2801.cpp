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

const int N=200;
const double eps=1e-10;

int dcmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}

int n;
Point a[N][3];

double Intersec(Point a,Point b,double x)
{
	return (a.y-b.y)/(a.x-b.x)*(x-a.x)+a.y;
}

double f(double x)
{
	static PDD q[N];
	int cnt=0;
	for(int i=0;i<n;i++) {
		if(x>=a[i][2].x || x<=a[i][0].x) continue;
		if(!dcmp(x,a[i][0].x) && !dcmp(x,a[i][1].x))
			q[++cnt]=PDD(a[i][0].y,a[i][1].y);
		else if(!dcmp(x,a[i][1].x) && !dcmp(x,a[i][2].x))
			q[++cnt]=PDD(a[i][1].y,a[i][2].y);
		else if(x<=a[i][1].x) 
			q[++cnt]=PDD(Intersec(a[i][0],a[i][1],x),Intersec(a[i][0],a[i][2],x));
		else q[++cnt]=PDD(Intersec(a[i][1],a[i][2],x),Intersec(a[i][0],a[i][2],x));
		
		if(q[cnt].x>q[cnt].y) swap(q[cnt].x,q[cnt].y);
	}
	if(cnt==0) return 0;
	
	sort(q+1,q+cnt+1);
	double st=q[1].x,ed=q[1].y,res=0;
	for(int i=2;i<=cnt;i++) {
		if(q[i].x<=ed) ed=max(ed,q[i].y);
		else {
			res+=ed-st;
			st=q[i].x,ed=q[i].y;
		}
	}
	return res+ed-st;
}

double area(double l,double r)
{
	double mid=(l+r)/2;
	return (r-l)*(f(l)+4*f(mid)+f(r))/6;
}

double simpson(double l,double r,double s)
{
//	printf("%.2lf %.2lf : %.5lf\n",l,r,s);
	double mid=(l+r)/2;
	double left=area(l,mid),right=area(mid,r);
	if(fabs(left+right-s)<eps && r-l<1e-1) return left+right;
	else return simpson(l,mid,left)+simpson(mid,r,right);
}

int main()
{
//	freopen("1.in","r",stdin);
	double l=1e6,r=0;
	cin>>n;
	for(int i=0;i<n;i++) {
		for(int j=0;j<3;j++)
			cin>>a[i][j].x>>a[i][j].y;
		sort(a[i],a[i]+3);
		
		l=min(l,a[i][0].x),r=max(r,a[i][2].x);
	}
//	l-=0.5,r+=0.5;
	printf("%.2lf\n",simpson(l,r,area(l,r)));
	
//	printf("%.2lf\n",simpson(0,1,area(0,1)));
//	printf("%.2lf\n",simpson(1,2,area(1,2)));
//	printf("%.2lf\n",simpson(2,3,area(2,3)));
	return 0;
}

