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

const int N=2048;
const double INF=1e16,eps=1e-5;

int n;
double a[N],b[N],h[N];
double dis[N];
bool vis[N];

double Prim(double t)
{
	int i,j,x;
	for(i=0;i<=n;i++) dis[i]=INF,vis[i]=false;
	dis[1]=0;
	double z,res=0;
	for(i=1;i<=n;i++) {
		for(x=0,j=1;j<=n;j++) 
			if(!vis[j]&&dis[j]<dis[x]) 
				x=j;
		
		vis[x]=true;
		res+=dis[x];
		for(j=1;j<=n;j++) {
			if(vis[j]) continue;
			z=fabs(h[j]-h[x])-t*sqrt(pow(a[x]-a[j],2)+pow(b[x]-b[j],2));
			if(dis[j]>z) dis[j]=z;
		}
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	while(scanf("%d",&n),n) {
		for(i=1;i<=n;i++) 
			scanf("%lf%lf%lf",&a[i],&b[i],&h[i]);
		
		double L=0,R=1e7,mid;
		while(L+eps<R) {
			mid=(L+R)/2;
			if(Prim(mid)>=0) L=mid;
			else R=mid;
		}
		printf("%.3lf\n",L);
	}
	return 0;
}

