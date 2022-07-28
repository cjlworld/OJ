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

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
double get_length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }

const int N=4e4+5;
int n;
Point a[N];

int stk[N],tt;
bool used[N];

double Andrew()
{
	int i;
	sort(a+1,a+n+1);
	
	for(i=1;i<=n;i++) {
//		printf("( %lf , %lf )\n",a[i].x,a[i].y);
		while(tt>=2 && cross(a[i]-a[stk[tt-1]],a[stk[tt]]-a[stk[tt-1]])<0)
			tt--;
		stk[++tt]=i;
	}
	for(i=2;i<=tt;i++) used[stk[i]]=true;
	for(i=n;i>=1;i--) {
		if(used[i]) continue;
		while(tt>=2 && cross(a[i]-a[stk[tt-1]],a[stk[tt]]-a[stk[tt-1]])<0)
			tt--;
		stk[++tt]=i;
	}

	double res=0;
	for(i=2;i<=tt;i++) 
		res+=get_length(a[stk[i]]-a[stk[i-1]]);

	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lf%lf",&a[i].x,&a[i].y);
		
	printf("%.2lf",Andrew());
	return 0;
}

