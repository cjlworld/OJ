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

inline Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
inline double cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }

const int N=700+5;

int n,ans;
Point a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	
	cin>>n;
	for(i=1;i<=n;i++) 
		cin>>a[i].x>>a[i].y;
	
	for(i=1;i<=n;i++) 
		for(j=i+1;j<=n;j++) {
			int cnt=2;
			for(k=j+1;k<=n;k++) {
				if(!sign(cross(a[k]-a[i],a[k]-a[j])))
					cnt++;
			}
			ans=max(ans,cnt);
		}
	
	cout<<ans<<endl;
	return 0;
}

