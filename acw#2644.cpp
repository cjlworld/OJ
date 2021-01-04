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

const int N=200,M=2e5+5,MOD=20110520;

int h[2][M],q[2][M],cnt[2];
LL v[2][M];

int Hash(int cur,int t)
{
	int u=t%M;
	while(~h[cur][u] && h[cur][u]!=t) 
		if(++u==M) u=0;
	return u;
}

void insert(int cur,int state,LL w)
{
	int u=Hash(cur,state);
	if(h[cur][u]==-1) {
		h[cur][u]=state;
		v[cur][u]=w%MOD;
		q[cur][++cnt[cur]]=u;
	}
	else v[cur][u]=(v[cur][u]+w)%MOD;
}

// 0 表示没有插头下来。
// 1 表示有插头下来，并且可以拐弯。
// 2 有但表示不可以拐弯。

int ask(int x,int y) { return (x>>2*y)&3; }
int make(int j,int t) { return t<<2*j; }

int n,m;
int a[N][N];
int endx,endy;
LL ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		string str;
		cin>>str;
		for(j=1;j<=m;j++) 
			if(str[j-1]=='_') a[i][j]=1;
	}
	
	// 令行数较多。 
	if(m>10) {
		for(i=1;i<=m;i++) 
			for(j=1;j<i;j++) 
				swap(a[i][j],a[j][i]);
		swap(n,m);
		
//		for(i=1;i<=n;i++,printf("\n")) 
//			for(j=1;j<=m;j++)
//				printf("%d ",a[i][j]);
	} 
	
	// find the last coin.
	for(i=n;i>=1 && !endy;i--)
		for(j=m;j>=1 && !endy;j--) 
			if(a[i][j]) 
				endx=i,endy=j;
	
	memset(h,-1,sizeof h);
	int cur=0,lt,state;
	LL w;
	insert(cur,0,1);
	
	for(i=1;i<=n;i++) {
		for(j=1;j<=cnt[cur];j++)
			h[cur][q[cur][j]]<<=2;
		
		for(j=1;j<=m;j++) {
			lt=cur,cur^=1;
			memset(h[cur],-1,sizeof h[cur]);
			cnt[cur]=0;
			
			for(k=1;k<=cnt[lt];k++) {
				state=h[lt][q[lt][k]],w=v[lt][q[lt][k]];
				x=ask(state,j-1),y=ask(state,j);
				
				// 不可走。
				if(!a[i][j]) {
					if(x==0 && y==0)
						insert(cur,state,w);
				}
				
				else if(i==endx && j==endy) {
					if((x==2 && y==0) || (y==2 && x==0) || (x==1 && y==1))
						ans=(ans+w)%MOD;
				}
				// 否则可走. 
				// A. 若 x==0 && y==0 ,
					// 1. 拐点。 
					// 2. right 
					// 3. down
				else if(x==0 && y==0) {
					if(a[i+1][j] && a[i][j+1]) 
						insert(cur,state+make(j-1,2)+make(j,2),w);
					if(a[i+1][j]) insert(cur,state+make(j-1,1),w);
					if(a[i][j+1]) insert(cur,state+make(j,1),w);
				}
				
				// B. 若 x==1 && y==0
				// 1. right , 2. down
				else if(x==1 && y==0) {
					if(a[i][j+1]) insert(cur,state-make(j-1,1)+make(j,1),w);
					if(a[i+1][j]) insert(cur,state-make(j-1,1)+make(j-1,2),w);
				} 
				
				// C. 若 x==2 && y==0
				// 1. right 
				else if(x==2 && y==0) {
					if(a[i][j+1]) insert(cur,state-make(j-1,2)+make(j,2),w);
					insert(cur,state-make(j-1,2),w);
				} 
				
				// D. 若 x==0 && y==1
				// 1. right , 2.down
				else if(x==0 && y==1) {
					if(a[i][j+1]) insert(cur,state-make(j,1)+make(j,2),w);
					if(a[i+1][j]) insert(cur,state-make(j,1)+make(j-1,1),w); 
				} 
				
				// E. 若 x==0 && y==2
				// 1. down;
				else if(x==0 && y==2) {
					if(a[i+1][j]) insert(cur,state-make(j,2)+make(j-1,2),w);
					insert(cur,state-make(j,2),w);
				} 
				
				// F. 若 x==1 && y==1
				// end in this coin
				else if(x==1 && y==1) {
					insert(cur,state-make(j-1,1)-make(j,1),w);
				}
				
				// G. x==1 && y==2
				// H. x==2 && y==1
				// I. x==2 && y==2
				// let it burn!
			}
		}
	}
	
	printf("%lld\n",ans);
	return 0;
}

