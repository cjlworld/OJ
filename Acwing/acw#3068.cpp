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
typedef pair<LL,LL> PLL;
typedef PLL Point;

#define x first
#define y second

const int N=1e5+5;

Point a[N][2];
vector<LL> xs;
int n;

PLL q[N];

LL area(LL l,LL r)
{
	int i;
	int cnt=0;
	for(i=1;i<=n;i++) {
		if(a[i][0].x<=l && a[i][1].x>=r) 
			q[++cnt]=PLL(a[i][0].y,a[i][1].y);
	}
	if(cnt==0) return 0; // be careful;
	sort(q+1,q+cnt+1);
	LL st=q[1].x,ed=q[1].y,res=0;
	for(i=2;i<=cnt;i++) {
		if(q[i].x<=ed) ed=max(ed,q[i].y);
		else {
			res+=ed-st;
			st=q[i].x,ed=q[i].y;
		}
	}
	res+=ed-st; // be careful
	return res*(r-l);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%lld%lld%lld%lld",&a[i][0].x,&a[i][0].y,&a[i][1].x,&a[i][1].y);
		xs.push_back(a[i][0].x);
		xs.push_back(a[i][1].x);
	}
	
	sort(xs.begin(),xs.end());
	xs.erase(unique(xs.begin(),xs.end()),xs.end());
	
	LL ans=0;
	for(i=1;i<(int)xs.size();i++) 
		ans+=area(xs[i-1],xs[i]);
	
	printf("%lld\n",ans);
	return 0;
}

