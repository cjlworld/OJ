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

const double eps=1e-12,PI=acos(-1);

int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}
int sign(double x) { return cmp(x,0); } 

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); } 
Vector operator+(Vector a,Vector b) { return Vector(a.x+b.x,a.y+b.y); } 
Vector operator*(double a,Vector b) { return Vector(a*b.x,a*b.y); }
Vector operator/(Vector a,double b) { return Vector(a.x/b,a.y/b); }
double dot(Vector a,Vector b) { return a.x*b.x+a.y*b.y; }
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
Vector rotate(Vector a,double b) { return Vector(a.x*cos(b)+a.y*sin(b),-a.x*sin(b)+a.y*cos(b)); } 
double length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); } 
double dist(Point a,Point b) { return length(a-b); }

struct Line
{
	Point p;
	Vector v;
	Line(Point p,Vector v) : p(p),v(v) {}
	Line() {} 
};

Point Intsec(const Line &a,const Line &b) 
{
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
inline bool inCircle(Point a,const Circle &c) { return cmp(dist(c.p,a),c.r)<=0; }

const int N=1e5+5;

int n;
Point a[N];
double cta,p;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lf%lf",&a[i].x,&a[i].y);
	scanf("%lf%lf",&cta,&p);
	cta=cta/180*PI;
	for(i=1;i<=n;i++) {
		a[i]=rotate(a[i],cta);
		a[i].x/=p;
	}
//	for(i=1;i<=n;i++) printf("%lf %lf\n",a[i].x,a[i].y);
	
	Circle c(a[1],0);	
	for(i=2;i<=n;i++) {
		if(inCircle(a[i],c)) continue;
		c=Circle(a[i],0);
		for(j=1;j<=i-1;j++) {
			if(inCircle(a[j],c)) continue;
			
			c=Circle((a[i]+a[j])/2,dist(a[i],a[j])/2);
			
			for(k=1;k<=j-1;k++) {
				if(inCircle(a[k],c)) continue;
				c=GetCircle(a[i],a[j],a[k]);
			}
		}
	}
	
	printf("%.3lf\n",c.r);
	return 0;
}

