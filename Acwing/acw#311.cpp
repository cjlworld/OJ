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

int Mod;
int dim[13];
LL f[13][92][92];
// f[i][j][k] 表示已经填到第i位，
// [top--j] 所构成的十进制数%Mod==j, [top--j] 加起来=k 的方案数。 

LL dfs(int now,int yu,int sum,bool lt)
{
	if(now==1) return (yu==0&&sum==Mod);
	if(!lt&&f[now][yu][sum]!=-1) 
		return f[now][yu][sum];
	LL res=0;
	int maxn=((lt ? dim[now-1] : 9));
	for(int i=0;i<=maxn;i++) 
		res+=dfs(now-1,(yu*10+i)%Mod,sum+i,lt&&i==maxn);
	if(!lt) f[now][yu][sum]=res;
	return res;
}

LL count(LL x)
{
	memset(dim,0,sizeof dim);
	int top=0;
	while(x) dim[++top]=x%10,x/=10;
	return dfs(top+1,0,0,true);
}

int main()
{
//	freopen("1.in","r",stdin);
	LL L,R,ans=0;
	cin>>L>>R;
	for(Mod=1;Mod<=90;Mod++) {
		memset(f,-1,sizeof f);
		ans+=count(R)-count(L-1);
	}
	printf("%lld\n",ans);
	return 0;
}

