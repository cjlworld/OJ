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

const int N=3000+5,INF=1e9+5;

int f[N][N]; // f[i][j] 表示 >= i 升O2 ，和 >=j升 N2 所要的最小质量 
int o2[N],n2[N],w[N];
int toto,totn,n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>toto>>totn>>n;
	for(i=1;i<=n;i++)
		cin>>o2[i]>>n2[i]>>w[i];
	
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	
	for(i=1;i<=n;i++) 
		for(j=toto;j>=0;j--) 
			for(k=totn;k>=0;k--) 
				f[j][k]=min(f[j][k],f[max(0,j-o2[i])][max(0,k-n2[i])]+w[i]);
	
	cout<<f[toto][totn];
	return 0;
}

