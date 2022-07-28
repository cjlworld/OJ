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
int n,m;
int f[N][N];
int v[N],w[N];
bool g[N][N];

void findway(int x,int y)
{
	if(g[x][y]) return;
	g[x][y]=true; 
	if(x==1) return;
	if(f[x-1][y]==f[x][y]) findway(x-1,y);
	if(y>=v[x]&&f[x-1][y-v[x]]+w[x]==f[x][y]) findway(x-1,y-v[x]);
	return;
}
void printway(int x,int y)
{
	if(x==n) return;
	if(g[x+1][y+v[x+1]]) printf("%d ",x+1),printway(x+1,y+v[x+1]);
	else printway(x+1,y);
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		cin>>v[i]>>w[i];
		
	memset(f,0xc0,sizeof f);
	f[0][0]=0;
	
	for(i=1;i<=n;i++) 
		for(j=0;j<=m;j++) {
			f[i][j]=f[i-1][j];
			if(j>=v[i]) f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
		}
	int ans=0;
	for(i=0;i<=m;i++) ans=max(ans,f[n][i]);
	for(i=0;i<=m;i++) 	
		if(f[n][i]==ans) 
			findway(n,i);
	printway(0,0);
	return 0;
}
