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
typedef pair<LL,int> PLI;

const int N=1e5+5;

struct Equip
{
	LL a,b,c,d;
	bool operator<(const Equip &t) const
	{
		if(a!=t.a) return a<t.a;
		else return b<t.b;
	}
}a[N];

priority_queue<PLI,vector<PLI>,greater<PLI> > q;

int n;
LL fy;

bool check(LL t)
{
	LL x=t,y=0,z;
	fy=0;
	while(q.size()) q.pop();
	for(int j=1;j<=n||q.size();) {
		for(;j<=n && a[j].a<=x;j++) 
			q.push(PLI(a[j].b,j));
			
		while(q.size()&&q.top().first<=y) {
			z=q.top().second; q.pop();
			x+=a[z].c,y+=a[z].d;
			
			for(;j<=n && a[j].a<=x;j++) 
				q.push(PLI(a[j].b,j));
		}

		if(q.empty()&&j<=n)  // x ²»¹» 
			return false;
		else if(q.size()) {  // y ²»¹» 
			z=q.top().second; 
			fy+=a[z].b-y;
			y=a[z].b;
		}
	}
	return true;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	cin>>n; 
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld%lld%lld%lld",&a[i].a,&a[i].b,&a[i].c,&a[i].d);
	sort(a+1,a+n+1);
	
	LL L=-1,R=1e9+5,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	check(R);
	cout<<R<<" "<<fy<<endl;
	
	return 0;
}

