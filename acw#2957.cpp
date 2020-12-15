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
#define double long double
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<double,double> PDD;
typedef PDD Point;
typedef PDD Vector;

#define x first
#define y second

const double eps=1e-18,PI=acos(-1);

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
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }

const int N=2e5+5;

struct Line
{
	Point p;
	Vector v;
	int id;
	Line(Point p,Vector v,int id) : p(p),v(v),id(id) {}
	Line() {}
}c[N];

double Get_angle(const Line &a) { return atan2(a.v.y,a.v.x); }
inline bool operator<(const Line &a,const Line &b)
{
	double k1=Get_angle(a),k2=Get_angle(b);
	if(!cmp(k1,k2)) return cross(a.v,b.p-a.p)<0;
	else return k1<k2;
}

Point getIN(const Line &a,const Line &b)
{
	double w=(cross(a.p,a.v)+cross(a.v,b.p))/cross(b.v,a.v);
	return b.p+w*b.v;
}
bool On_right(const Point &a,const Line &b) { return sign(cross(a-b.p,b.v))>0; }

int n;

int q[N];
int hh=0,tt=-1;

void half_plane()
{	
	sort(c+1,c+n+1);
	for(int i=1;i<=n;i++) {
//		printf("%d\n",c[i].id);
		if(i>0 && !cmp(Get_angle(c[i]),Get_angle(c[i-1]))) continue; 
		while(hh<tt && On_right(getIN(c[q[tt]],c[q[tt-1]]),c[i])) tt--;
		while(hh<tt && On_right(getIN(c[q[hh]],c[q[hh+1]]),c[i])) hh++;
		q[++tt]=i;
	}
	
	while(hh<tt && On_right(getIN(c[q[tt]],c[q[tt-1]]),c[q[hh]])) tt--;
	while(hh<tt && On_right(getIN(c[q[hh]],c[q[hh+1]]),c[q[tt]])) hh++;
}

int ans[N],cnt;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&x),c[i].p.y=x;
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		c[i].v.x=1,c[i].v.y=x;
		c[i].id=i;
	}
	n++,c[n]=Line(Point(0,0),Vector(0,-1),n);
	n++,c[n]=Line(Point(0,0),Vector(1,0),n);
	
	half_plane();

	for(i=hh,cnt=0;i<=tt;i++)
		if(c[q[i]].id<=n-2) {
			ans[++cnt]=c[q[i]].id;
			
			for(j=q[i]+1;j<=n && !cmp(Get_angle(c[j]),Get_angle(c[q[i]]));j++) 
				if(!cmp(c[j].p.y,c[q[i]].p.y))
					ans[++cnt]=c[j].id;
					
			for(j=q[i]-1;j>=1 && !cmp(Get_angle(c[j]),Get_angle(c[q[i]]));j--) 
				if(!cmp(c[j].p.y,c[q[i]].p.y))
					ans[++cnt]=c[j].id;
		}
			
	
	sort(ans+1,ans+cnt+1);
	printf("%d\n",cnt);
	for(i=1;i<=cnt;i++) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}

