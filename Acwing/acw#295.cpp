#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=1e5+5;

int n,s,t;
struct Len
{
	int l,r;
	bool operator<(const Len &t) const
	{
		return l<t.l||(l==t.l&&r<t.r);
	}
}a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d",&n,&t);
	for(i=1;i<=n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1);
	// s 表示已经覆盖了 1--->s  
	i=1;
	int pos=s,ans=0;
	while(s<t) {
		for(;a[i].l<=s+1&&i<=n;i++) 
			pos=max(pos,a[i].r);
		if(pos<=s) {
			printf("-1\n");
			return 0;
		}
		s=pos;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}

