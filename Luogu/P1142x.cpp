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

inline int cmp(double x,double y)
{
	if(fabs(x-y)<eps) return 0;
	else if(x>y) return 1;
	else return -1;
}
inline int sign(double x) { return cmp(x,0); }

inline double slope(Point a,Point b) { return (a.x-b.x)/(a.y-b.y); }
const int N=700+5;

int n,ans;
Point a[N];

double f[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	cin>>n;
	for(i=1;i<=n;i++) 
		cin>>a[i].x>>a[i].y;
	
	for(i=1;i<=n;i++) {
		int tot=0;
		for(j=i+1;j<=n;j++) 
			f[++tot]=slope(a[i],a[j]);
		sort(f+1,f+tot+1);
		
		int sum=2;
		for(j=2;j<=tot;j++) {
			ans=max(ans,sum);
			if(!cmp(f[j],f[j-1])) sum++;
			else sum=2;
		}
		ans=max(ans,sum);
	}
	
	cout<<ans<<endl;
	return 0;
}

