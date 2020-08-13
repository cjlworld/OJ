#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=2e5+5;
const int K=50+5;
vector<int> v[K];
int n,k,p;
int b[N];
int f[N][21];
inline int query(int l,int r)
{
	int tmp=floor(log2(r-l+1));
	return min(f[l][tmp],f[r-(1<<tmp)+1][tmp]);
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x;
	scanf("%d%d%d",&n,&k,&p);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&x,&f[i][0]);
		v[x].push_back(i);
	}
	for(i=1;i<=20;i++) 
		for(j=1;j+(1<<i)-1<=n;j++) 
			f[j][i]=min(f[j][i-1],f[j+(1<<(i-1))][i-1]);
	int L,R,mid;
	LL ans=0;
	for(i=0;i<=k-1;i++) {
		for(j=0;j<(int)v[i].size()-1;j++) {
			L=j; R=v[i].size()-1;
			if(L+1==R) {
				ans+=(LL)(query(v[i][L],v[i][R])<=p);
				continue;
			}
			while(L+1<R) {
				mid=(L+R)>>1;
				if(query(v[i][j],v[i][mid])<=p) R=mid;
				else L=mid;
			}
			ans+=(LL)((LL)v[i].size()-R);
		}
	}
	printf("%lld",ans);
	return 0;
}

