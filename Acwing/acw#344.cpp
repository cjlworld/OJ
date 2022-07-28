#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=100+5,INF=0x3f3f3f3f;

int w[N][N],f[N][N],g[N][N];
int n,m;

inline void tense(int &a,const int &b) { a=((a<b) ? a : b); }

vector<int> v;
void dfs(int x,int y)
{
	if(!x||!y||!g[x][y]) return;
	dfs(x,g[x][y]);
	v.push_back(g[x][y]);
	dfs(g[x][y],y);
}

void getpath(int x,int y,int z)
{
	v.clear();
	v.push_back(z);
	v.push_back(x);
	dfs(x,y);
	v.push_back(y);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof f);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		tense(f[x][y],z);
		tense(f[y][x],z);
	}
	memcpy(w,f,sizeof w);
	
	int ans=INF;
	for(k=1;k<=n;k++) {
		for(i=1;i<k;i++) 
			for(j=1;j<k;j++) {
				if(i!=j && w[i][k]<INF && w[k][j]<INF 
					&& f[i][j]<INF && ans>f[i][j]+w[i][k]+w[k][j]) {
					ans=f[i][j]+w[i][k]+w[k][j];
					getpath(i,j,k);
				}
			}
		
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) {
				if(f[i][k]+f[k][j]<f[i][j]) {
					f[i][j]=f[i][k]+f[k][j];
					g[i][j]=k;
					
//					printf("f[%d][%d] = %d\n",i,j,f[i][j]);
				}
			}
	}
//	cout<<ans<<endl;
	if(ans==INF) printf("No solution.\n");	
	else {
		for(i=0;i<(int)v.size();i++) 
			printf("%d ",v[i]);
		printf("\n");
	}
	return 0;
}
