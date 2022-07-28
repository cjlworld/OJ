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

const int N=1024;

int n;
double d;

struct Seg
{
	double l,r;
	inline bool operator<(const Seg &t) const
	{
		return r<t.r;
	}
}a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	double x,y,r;
	
	cin>>n>>d;
	for(i=1;i<=n;i++) {
		cin>>x>>y;
		if(y>d) {
			printf("-1");
			return 0;
		}	
		r=sqrt(d*d-y*y);
		a[i].l=x-r,a[i].r=x+r;
	}
	sort(a+1,a+n+1);
	double t=-1e16;
	int ans=0;
	for(i=1;i<=n;i++) 
		if(a[i].l>t) 
			t=a[i].r,ans++;
	cout<<ans<<endl;
	return 0;
}

