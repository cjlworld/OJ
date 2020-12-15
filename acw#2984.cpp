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

int sign(double x)
{
	if(fabs(x)<eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}

double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }
Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }

const int N=500+5;

int T,n,tot;
Point a[N],b[N],q[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	
	scanf("%d",&T);
	
	while(T--) {
		tot=0;
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			scanf("%lf%lf%lf%lf",&a[i].x,&a[i].y,&b[i].x,&b[i].y);
			q[++tot]=a[i],q[++tot]=b[i];
		}
		
		bool flag=false;
		for(i=1;i<=tot;i++) {
			for(j=i+1;j<=tot;j++) {
				if(!cmp(q[i].x,q[j].x) && !cmp(q[i].y,q[j].y)) continue;
				
				for(k=1;k<=n;k++) { // check 
					if(sign(cross(q[j]-q[i],a[k]-q[i]))*sign(cross(q[j]-q[i],b[k]-q[i]))>0)
						break;
				}
				
				if(k>n) flag=true;
			}
			if(flag) break;
		}
		if(flag) printf("Yes!\n");
		else printf("No!\n");
	}
	
	return 0;
}

