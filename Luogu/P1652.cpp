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

const double eps=1e-8,PI=acos(-1);

int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}
int sign(double x) { return cmp(x,0); }

const int N=1100+5;
Point center[N];
double r[N];

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
double get_length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }
bool inCircle(Point a,int c) { return cmp(get_length(a-center[c]),r[c])==-1; }

int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	Point a,b;
	int ans=0;
	
	cin>>n;
	for(i=1;i<=n;i++) cin>>center[i].x;
	for(i=1;i<=n;i++) cin>>center[i].y;
	for(i=1;i<=n;i++) cin>>r[i];
	
	cin>>a.x>>a.y>>b.x>>b.y;
	for(i=1;i<=n;i++) 
		ans+=(inCircle(a,i)^inCircle(b,i));
	cout<<ans<<endl;
	return 0;
}

