#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=32767+5;
const int INF=(-1u)>>1;
int n;
LL ans=0;
set<int> S;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	set<int>::iterator it;
	scanf("%d",&x);
	ans=x;
	S.insert(x);
	for(i=2;i<=n;i++) {
		scanf("%d",&x);
		it=S.lower_bound(x);
		y=INF;
		if(it!=S.end()) y=*it-x;
		if(*S.begin()<x)   {
			it--;
			y=min(x-*it,y);
		}
		ans+=y;
		S.insert(x);
	}
	cout<<ans;
	return 0;
}

