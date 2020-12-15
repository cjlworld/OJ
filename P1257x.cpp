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
typedef pair<int,int> PII;
typedef PII Point;

#define x first
#define y second

const int N=1e5+5,INF=0x3f3f3f3f;

int n;
Point a[N];
multiset<PII> S;
double ans;

double dist(Point a,Point b)
{
	double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

int main()
{
//	freopen("1.in","r",stdin);
	
	int i;
	multiset<PII>::iterator it;
	
	scanf("%d",&n);
	S.clear(),ans=INF;
	for(i=1;i<=n;i++) 
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	
	int hh=1; // 横座标之差 < ans 的最小的队头。
	for(i=1;i<=n;i++) {
		while(hh<i && a[i].x-a[hh].x>=ans) S.erase(PII(a[hh].y,a[hh].x)),hh++;
		for(it=S.lower_bound(PII(a[i].y-ans,-INF));it!=S.end() && it->first-a[i].y<ans;it++)
			ans=min(ans,dist(a[i],Point(it->second,it->first)));
		S.insert(PII(a[i].y,a[i].x));
	} 
	
	printf("%.4lf\n",ans);
	
	return 0;
}

