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

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
Vector operator+(Vector a,Vector b) { return Vector(a.x+b.x,a.y+b.y); }
Vector operator*(double a,Vector b) { return Vector(a*b.x,a*b.y); }
int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}
int sign(double x) { return cmp(x,0); }
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }

const int N=1e4+5;

int n,m,cnt;
Point a[N];

struct Line
{
	Point p;
	Vector v;
}c[N];

double Getangle(Line a) { return atan2(a.v.y,a.v.x); } 
inline bool operator<(const Line &a,const Line &b)
{
	double k1=Getangle(a),k2=Getangle(b);
	if(!cmp(k1,k2)) return cross(a.v,b.p-a.p)<0;
	else return k1<k2;
}

bool On_right(Point a,Line b) { return sign(cross(a-b.p,b.v))>=0; }

Point getIN(Line a,Line b)
{
	double w=(cross(a.p,a.v)+cross(a.v,b.p))/cross(b.v,a.v);
	return b.p+w*b.v;
}

int q[N];


void half_plane()
{
	int i;
	int hh=0,tt=-1;

	sort(c+1,c+cnt+1);
	
	for(i=1;i<=cnt;i++) {
		if(i>1 && !cmp(Getangle(c[i]),Getangle(c[i-1]))) continue;
		while(hh<tt && On_right(getIN(c[q[tt]],c[q[tt-1]]),c[i])) tt--;
		while(hh<tt && On_right(getIN(c[q[hh]],c[q[hh+1]]),c[i])) hh++;
		q[++tt]=i;
	}

	while(hh<tt && On_right(getIN(c[q[tt]],c[q[tt-1]]),c[q[hh]])) tt--;
	while(hh<tt && On_right(getIN(c[q[hh]],c[q[hh+1]]),c[q[tt]])) hh++;
	
	q[tt+1]=q[hh];
	for(i=hh,n=0;i<=tt;i++) 
		a[++n]=getIN(c[q[i]],c[q[i+1]]);
}

double area(Point a[],int n)
{
	double res=0;
	for(int i=2;i<n;i++) 
		res+=cross(a[i]-a[1],a[i+1]-a[1]);
	return res/2;
}

int main()
{
	int i;
	
	scanf("%d",&n);
	while(n--) {
		scanf("%d",&m);
		for(i=1;i<=m;i++) 
			scanf("%lf%lf",&a[i].x,&a[i].y);
		a[m+1]=a[1];
		for(i=1;i<=m;i++) {
			cnt++;
			c[cnt].p=a[i],c[cnt].v=a[i+1]-a[i];
		}
	}
	
	half_plane();
	printf("%.3lf",area(a,n));
	
	return 0;
}

