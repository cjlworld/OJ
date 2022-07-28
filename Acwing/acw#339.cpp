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

const int N=1024;

LL f[N][N]; // f[i][j] 表示后 f 位有 j 个1的方案数。 
int dim[N];

LL dfs(int now,int sum,bool lit) // f[now][sum] 
{
	if(sum<0) return 0ll;
	else if(now==0) return (sum==0);
	else if(f[now][sum]!=-1&&!lit) return f[now][sum];
	LL res=0;
	int maxn=(lit) ? dim[now] : 1;
	for(int i=0;i<=maxn;i++) 
		res+=dfs(now-1,sum-i,lit&&i==maxn);
	if(!lit) f[now][sum]=res;
	return res;
}

LL prefix(LL x)
{
	memset(dim,0,sizeof dim);
	int top=0;
	while(x) dim[++top]=x&1,x>>=1;
	LL res=0;
	int i,j;
	for(i=2;i<=top;i++) // 枚举位数 
		for(j=1;j<=i/2;j++) // 枚举1的个数 
			res+=dfs(i-1,j-1,i==top); // 先在最高位填1； 
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	LL x,y;
	cin>>x>>y;
//	cout<<prefix(1)<<endl;
//	cout<<prefix(12)<<endl;
	cout<<prefix(y)-prefix(x-1)<<endl;
	return 0;
}

