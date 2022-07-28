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
#include<complex>
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

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
double length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }
double dist(Point a,Point b) { return length(a-b); }

const int N=1e4+5,INF=0x3f3f3f3f;

int n,m;
double R;
int ans=-INF;
Point a[N],b[N];
double r[N];

inline double rnd(double l,double r)
{
	return rand()*(r-l)/RAND_MAX+l;
}

int calc(Point cur)
{
	int i,res=0;
	double nowr=R;
	for(i=1;i<=n;i++) 
		nowr=min(nowr,dist(a[i],cur)-r[i]);
	for(i=1;i<=m;i++) 
		if(dist(b[i],cur)<=nowr) 
			res++;
	ans=max(ans,res); // 取过程中的最值为答案。 
	return res;
}

void SA()
{
	Point cur(b[rand()%m+1]);	
	for(double t=4e4;t>1e-6;t*=0.9) {
		PDD nw(rnd(cur.x-t,cur.x+t),rnd(cur.y-t,cur.y+t));
		double d=calc(nw)-calc(cur);
		
		if(d>0) cur=nw;
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i;
	
	cin>>n>>m>>R;
	for(i=1;i<=n;i++) 
		cin>>a[i].x>>a[i].y>>r[i];
	for(i=1;i<=m;i++) 
		cin>>b[i].x>>b[i].y;

	while(clock()<=CLOCKS_PER_SEC*0.9) SA();
	cout<<ans<<endl;
	return 0;
}
