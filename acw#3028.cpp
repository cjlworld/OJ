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

const double eps=1e-13,PI=acos(-1);
int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}
int sign(double x) { return cmp(x,0); }

Vector operator+(Vector a,Vector b) { return Vector(a.x+b.x,a.y+b.y); }
Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
Vector operator*(double a,Vector b) { return Vector(a*b.x,a*b.y); }
Vector operator/(Vector a,double b) { return Vector(a.x/b,a.y/b); }
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
double length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }
double dist(Point a,Point b) { return length(a-b); }
Vector rotate(Vector a,double b) { return Vector(a.x*cos(b)+a.y*sin(b),-a.x*sin(b)+a.y*cos(b)); }
struct Line
{
	Point p;
	Vector v;
	Line(Point p,Vector v) : p(p),v(v) {}
	Line() {}
};

Point Intsec(const Line &a,const Line &b)
{
//	double w=(cross(a.p,a.v)+cross(a.v,b.p))/cross(b.v,a.v);
	double w=cross(a.p-b.p,a.v)/cross(b.v,a.v);
	return b.p+w*b.v;
}

struct Circle
{
	Point p;
	double r;
	Circle(Point p,double r) : p(p),r(r) {}
	Circle() {}
};

Circle GetCircle(Point a,Point b,Point c)
{
	Line lab((a+b)/2,rotate(a-b,PI/2));
	Line lbc((b+c)/2,rotate(b-c,PI/2));
	
	Point d=Intsec(lab,lbc);
	return Circle(d,dist(a,d));
}

const int N=1e5+5;

int n;
Point a[N];

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i,j,k;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lf%lf",&a[i].x,&a[i].y);
	random_shuffle(a+1,a+n+1);
	
	Circle c(a[1],0);
	for(i=2;i<=n;i++) {
		if(cmp(dist(a[i],c.p),c.r)<=0) continue;
		c=Circle(a[i],0);
		
		for(j=1;j<=i-1;j++) {
			if(cmp(dist(a[j],c.p),c.r)<=0) continue;
			c=Circle((a[i]+a[j])/2,dist(a[i],a[j])/2);
			
			for(k=1;k<=j-1;k++) {
				if(cmp(dist(a[k],c.p),c.r)<=0) continue;
				c=GetCircle(a[i],a[j],a[k]);
			}
		}
	}
	
//	Point a(0,0),b(1,0),d(0,1);
//	c=GetCircle(a,b,d);
	printf("%.10lf\n%.10lf %.10lf\n",c.r,c.p.x,c.p.y);
	return 0;
}

