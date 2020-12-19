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

struct Line
{
	Point p;
	Vector v;
};

Point getIN(Line a,Line b)
{
	double w=(cross(a.p,a.v)+cross(a.v,b.p))/cross(b.v,a.v);
	return b.p+w*b.v;
}

PDD input()
{
	Point a;
	cin>>a.x>>a.y;
	return a;
}

Line read()
{
	Point a;
	Line c;
	c.p=input();
	a=input();
	c.v=a-c.p;
	return c;
}

int main()
{
//	freopen("1.in","r",stdin);
	int n;
	printf("INTERSECTING LINES OUTPUT\n");
    scanf("%d", &n);
    while (n -- )
    {
		Line c,d;
		c=read(),d=read();
		if(!sign(cross(c.v,d.v)) && !sign(cross(c.p-d.p,d.v))) printf("LINE\n");
		else if(!sign(cross(c.v,d.v))) printf("NONE\n");
		else {
			PDD o = getIN(c, d);
			printf("POINT %.2lf %.2lf\n",o.x,o.y);
		}
    }
    printf("END OF OUTPUT\n");
	return 0;
}

