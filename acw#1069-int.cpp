#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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
const int N=50;
#define int long long
int n;
int f[N][N];
int w[N];
signed main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,len;
	cin>>n;
	for(i=1;i<=n;i++) cin>>w[i];
	memset(f,0x3f,sizeof f);
	for(len=1;len<=n;len++) {
		for(i=1;i+len-1<=n;i++) {
			j=i+len-1;
			if(len==1||len==2) f[i][j]=0;
			else if(len==3) f[i][j]=w[i]*w[i+1]*w[j];
			else {
				for(k=i+1;k<=j-1;k++) 
					f[i][j]=min(f[i][j],f[i][k]+f[k][j]+w[i]*w[k]*w[j]);
			}		
		}
	}
	cout<<f[1][n];
	return 0;
}

