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

const int N=25,INF=1e9+5;
int n,m;
int a[N][N],f[N][N];
// f[step][tot] = w
// step 选了前 1 ~ step-1 的分公司，现在选step，已选了tot个设备 
// 最大盈利w 
int cnt[N][N];

void print(int x,int y)
{
	if(x==0) return;
	print(x-1,y-cnt[x][y]);
	printf("%d %d\n",x,cnt[x][y]);
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			cin>>a[i][j];
	
	memset(f,0xc0,sizeof f);
	f[0][0]=0;
	
	for(i=1;i<=n;i++) 
		for(j=0;j<=m;j++) // 选完后选了几个设备 
			for(k=0;k<=j;k++) { // 这一个分公司选了几个设备 
				if(f[i-1][j-k]+a[i][k]>f[i][j]) {
					f[i][j]=f[i-1][j-k]+a[i][k];
					cnt[i][j]=k;
				}
			}
	int ans=0;
	for(i=0;i<=m;i++) 
		if(f[n][i]>f[n][ans]) 
			ans=i;
	cout<<f[n][ans]<<endl;
	print(n,ans);
	
	return 0;
}

