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

const int N=64,INF=1e9+5;
//一套防御系统的导弹拦截高度要么一直 严格单调 上升要么一直 严格单调 下降。 
int n;
int a[N],b[N],c[N],totb,totc;
int ans;
void dfs(int step)
{
	if(totb+totc>=ans) return;
	if(step==n+1) {
		ans=totb+totc;
		return;
	}
	
	int Max=-1,p=-1,Min=INF,tmp,i;
	
	// 1. 选 严格单调 上升
	
	for(i=1;i<=totb;i++) {
		if(b[i]<a[step]&&b[i]>Max) 
			Max=b[i],p=i;
	}
	if(p!=-1) {
		tmp=b[p];
		b[p]=a[step];
		dfs(step+1);
		b[p]=tmp;
	} 
	else {
		b[++totb]=a[step];
		dfs(step+1);
		b[totb--]=0;
	}
	
    // 2. 选 严格单调 下降
	p=-1;
	for(i=1;i<=totc;i++) {
		if(c[i]>a[step]&&c[i]<Min)
			Min=c[i],p=i;
	}
	if(p!=-1) {
		tmp=c[p];
		c[p]=a[step];
		dfs(step+1);
		c[p]=tmp;
	}
	else {
		c[++totc]=a[step];
		dfs(step+1);
		c[totc--]=0;
	}
	
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	while(cin>>n,n) {
		memset(b,0,sizeof b);
		memset(c,0,sizeof c);
		totb=totc=0;
		ans=INF;
		
		for(i=1;i<=n;i++) cin>>a[i];
		dfs(1);
		cout<<ans<<endl;
	}
	return 0;
}

