#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
LL f[12][256];
LL mod;
LL dim[26];
LL dfs(int now,int md,bool lit)
{
	if(now==0) return (md==0) ? 1 : 0;
	if(!lit&&f[now][md]!=-1) 
		return f[now][md]; 
	LL res=0;
	int maxn=(lit) ? dim[now] : 9;
	for(int i=0;i<=maxn;i++) {
		res+=dfs(now-1,(md+i)%mod,(lit&&i==maxn));
	}
	if(!lit) 
		f[now][md]=res;
	return res;
}
LL prefix(LL x)
{
	int top=0;
	memset(dim,0,sizeof dim);
	while(x) {
		dim[++top]=x%10;
		x=x/10;
	}
	return dfs(top,0,true);
}
int main()
{
//	freopen("1.in","r",stdin);
	LL n,m;
	while(cin>>n>>m>>mod) {
		memset(f,-1,sizeof f);
		LL ans=prefix(m);
		memset(f,-1,sizeof f);
		ans-=prefix(n-1);
		cout<<ans<<endl;
	}
	return 0;
}

