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

const int N=256,INF=1e9+5; 
int f[N][N]; // f[i][j] 表示区间长度为i,手中有j个鸡蛋在最坏情况下所需要的扔鸡蛋次数。

int Dp(int x,int k) // 共有x层,保证在x+1层一定碎,有k个鸡蛋 
{
	if(x==0) return 0; // x==0,那么不用试,x==1 还要试一次, 若不是x层碎，就是x+1层碎。 
	else if(k==1) return x;
	int &v=f[x][k];
	if(v!=-1) return v;
	v=INF;	
	for(int i=1;i<=x;i++) // 枚举扔的楼层 
		v=min(v,max(Dp(i-1,k-1),Dp(x-(i+1)+1,k))+1); // 摔碎了，没摔碎。 
	return v; 
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	int x,k;
	while(cin>>x>>k) 
		cout<<Dp(x,k)<<endl;
	return 0;
}
