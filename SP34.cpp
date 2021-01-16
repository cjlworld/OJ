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

const int N=1000+5;

int n;
Point a[N];
double cmax;
Point ans;

double calc(Point cur)
{
    double res=1e9;
    for(int i=1;i<=n;i++) 
        res=min(res,dist(cur,a[i]));
    
    if(res>cmax) cmax=res,ans=cur;
    return res;
}

double rnd(double l,double r)
{
    return rand()*(r-l)/RAND_MAX+l;
}

double X,Y;

void SA()
{
    PDD cur(rnd(0,X),rnd(0,Y));
    for(double t=1e4;t>1e-4;t*=0.99) {
        PDD nw(rnd(max(cur.x-t,0.0),min(cur.x+t,X)),
			rnd(max(cur.y-t,0.0),min(cur.y+t,Y)));
        double d=calc(nw)-calc(cur);
//        if(d>0) cur=nw;
        if(exp(d/t)>rnd(0,1)) cur=nw;
        // exp(x)=pow(e,x)
//      cerr<<cur.x<<" "<<cur.y<<endl;
    }
}

int main()
{
//	freopen("1.in","r",stdin);
    srand((unsigned) time(0));
	
	int T;
	cin>>T;
	for(int Case=1;Case<=T;Case++) {
		cmax=-1e9;
	    cin>>X>>Y>>n;
	    for(int i=1;i<=n;i++)
	        cin>>a[i].x>>a[i].y;
	
	    for(int i=1;i<=100;i++) SA();
		printf("The safest point is (%.1lf, %.1lf).\n",ans.x,ans.y);
	}
    return 0;
}
