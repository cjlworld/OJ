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

const int N=100;
int n;
LL f[N][N],w[N];
int g[N][N];

void print(int l,int r)
{
	if(l>r) return;
	else if(l==r) {
		printf("%d ",l);
		return;
	}
	printf("%d ",g[l][r]);
	print(l,g[l][r]-1),print(g[l][r]+1,r);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,len,k;
	LL left,right;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&w[i]);
	for(i=1;i<=n;i++) 
		f[i][i]=w[i];
	for(len=2;len<=n;len++) {
		for(i=1;i+len-1<=n;i++) {
			j=i+len-1;
			for(k=i;k<=j;k++) {
				left=(k==i) ? 1 : f[i][k-1];
				right=(k==j) ? 1 : f[k+1][j];
				if(left*right+w[k]>f[i][j]) {
					f[i][j]=left*right+w[k];
					g[i][j]=k;
				} 
			}
		}
	}
	cout<<f[1][n]<<endl;
	print(1,n);
	return 0;
}

