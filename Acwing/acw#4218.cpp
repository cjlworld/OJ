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

const int N=17;
const int INF=0x3f3f3f3f;
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int n,m;
int a[N][N],c[N][N],ans[N][N];
int cnt,ans_cnt=INF;
void rev(int x,int y)
{
	if(c[x][y]) cnt--;
	else cnt++;
	
	c[x][y]^=1;
	a[x][y]^=1;
	for(int i=0;i<4;i++) {
		int nx=x+dx[i],ny=y+dy[i];
		a[nx][ny]^=1;
	}
}

void dfs(int x,int y) // 以位置为主要顺序搜索 
{
//	printf("(%d, %d)\n",x,y);
	if(x==n+1) {
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=m;j++) 
				if(a[i][j]) return;
		if(cnt<ans_cnt) {
			ans_cnt=cnt;
//			printf("here!\n");
			memcpy(ans,c,sizeof ans);
		}
		return;
	}
	
	int nx=x,ny=y+1;
	if(ny>m) ny-=m,nx++;
	
	if(x==1 || !a[x-1][y])
		dfs(nx,ny);
	
	if(x==1 || a[x-1][y]) {
		rev(x,y);
		dfs(nx,ny);
		rev(x,y); 
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	dfs(1,1);
	if(ans_cnt==INF) puts("IMPOSSIBLE");
	else {
//		printf("%d\n",ans_cnt);
		for(int i=1;i<=n;i++,puts("")) 
			for(int j=1;j<=m;j++) 
				printf("%d ",ans[i][j]);
	}
	return 0;
}

