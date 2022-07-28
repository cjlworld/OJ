#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const LL P=998244353; 
const int N=2000+5;

int n,m,k;
LL f[N][N],s[N];

int main()
{
//	freopen("1.in","r",stdin);
	
	cin>>n>>m>>k;
	f[1][0]=m;
	for(int i=2;i<=n;i++) {
		for(int j=0;j<=k;j++) {
			// f[i][j] = f[i-1][j] + f[i-1][j-1] * (m-1) 
			if(j>=1)
				f[i][j]=(f[i-1][j]+f[i-1][j-1]*(m-1)%P)%P; 
			else f[i][j]=f[i-1][j];
		}
	}
	printf("%lld\n",f[n][k]);
	return 0;
}

