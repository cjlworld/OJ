#include<set>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e5+5;
int n;
struct Bits
{
	int c[N]; // ei --> high=i , length max
	int res;
	inline int lowbit(const int &x) 
	{
		return x&(-x);
	}
	inline void update(int x,const int &y)
	{
		for(;x<=60000;x+=lowbit(x)) 
			c[x]=max(c[x],y);
		return;
	}
	inline int sum(int x)
	{
		res=0;
		for(;x>=1;x-=lowbit(x)) 
			res=max(res,c[x]);
		return res;
	}
}C;
int a[N],f[N];
int ans;
multiset<int> S;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	while(scanf("%d",&a[++n])==1);
	n--;
	for(i=1;i<=n;i++) {
		f[i]=C.sum(60000-a[i])+1;
		C.update(60000-a[i],f[i]);
	}
	for(i=1;i<=n;i++) 
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	ans=0;
	multiset<int> :: iterator it;
	for(i=1;i<=n;i++) {
		if(S.empty()||*(--S.end())<a[i]) {
			ans++;
			S.insert(a[i]); 
			continue;
		}
		it=S.lower_bound(a[i]);
		S.erase(it);
		S.insert(a[i]);
	}
	printf("%d\n",ans);
	return 0;
}

