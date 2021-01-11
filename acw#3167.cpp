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

const int N=100+5;

int n;
Point a[N];
double ans=1e9;

double calc(Point cur)
{
	double res=0;
	for(int i=1;i<=n;i++) 
		res+=dist(cur,a[i]);
	ans=min(ans,res);
	return res;
}

double rnd(double l,double r)
{
	return rand()*(r-l)/RAND_MAX+l;
}

void SA()
{
	PDD cur(rnd(0,1e4),rnd(0,1e4));
	for(double t=1e4;t>1e-6;t*=0.99) {
		PDD nw(rnd(cur.x-t,cur.x+t),rnd(cur.y-t,cur.y+t));
		double d=calc(nw)-calc(cur);
		if(exp(-d/t)>rnd(0,1)) cur=nw;
		// exp(x)=pow(e,x)
//		cerr<<cur.x<<" "<<cur.y<<endl;
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y;

	while(clock()<0.8*CLOCKS_PER_SEC) SA();
	cout<<(int)round(ans)<<endl;
	return 0;
}

