#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const LL P=19999999;
const int M=4001000;
int one[P+1],idx=1;
int cnt[M],ver[M],Next[M];
void insert(LL x)
{
	LL t=(x%P+P)%P;
	for(int i=one[t];i>0;i=Next[i]) {
		if(ver[i]==x) {
			cnt[i]++;
			return;
		}
	}
	Next[++idx]=one[t],one[t]=idx,ver[idx]=x,cnt[idx]=1;
}
int count(LL x)
{
	LL t=(x%P+P)%P;
	for(int i=one[t];i>0;i=Next[i]) 
		if(ver[i]==x) 
			return cnt[i];
	return 0;
}


const int N=10;

LL n,m;
LL a[N],p[N];
LL ans=0;

LL fpow(LL x,LL k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
LL sum=0;
void dfs1(int step,int r)
{
	if(step==r+1) return insert(sum);
	LL t,i;
	for(i=1;i<=m;i++) {
		t=a[step]*fpow(i,p[step]);
		sum+=t;
		dfs1(step+1,r);
		sum-=t;
	}
	return;
}

void dfs2(int step,int r)
{
	if(step==r+1) {
		ans+=count(-sum);
		return;
	}  
	LL t,i;
	for(i=1;i<=m;i++) {
		t=a[step]*fpow(i,p[step]);
		sum+=t;
		dfs2(step+1,r);
		sum-=t;
	}
	return;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
		cin>>a[i]>>p[i];
	dfs1(1,n/2);
	sum=0;
	dfs2(n/2+1,n);
	cout<<ans;
	return 0;
}
