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

const int N=20,M=2e5+5;

int h[2][M],q[2][M],cnt[2];
LL v[2][M];

bool check(int state);
void print(int state);
int Hash(int cur,int t)
{
	int u=t%M;
	while(~h[cur][u] && h[cur][u]!=t) 
		if(++u==M) u=0;
	return u;
}

void insert(int cur,int state,LL w)
{
//	print(state);
//	if(!check(state)) return (void)puts("here");
	int u=Hash(cur,state);
	if(h[cur][u]==-1) {
		h[cur][u]=state;
		v[cur][u]=w;
		q[cur][++cnt[cur]]=u;
	}
	else v[cur][u]+=w;
}

int ask(int x,int y) { return (x>>2*y)&3; }
int make(int j,int t) { return t<<2*j; }
int find(int state,int j,int val,int dec)
{
	for(int u,s=0;;j+=dec) {
		u=ask(state,j);
		if(u==0) continue;
		if(u!=val) s++;
		else if(--s==0) return j;
	}
	return -1;
}

int T;
int n,m;
int a[N][N];

bool check(int state)
{
	int s=0;
	for(int j=0;j<=m;j++) {
		int u=ask(state,j);
		if(u==0) continue;
		if(u==1) s++;
		else s--;
		if(s<0) return false;
	}
	return (s==0);
}
void print(int state)
{
	for(int j=0;j<=m;j++)
		printf("%d",ask(state,j));
	printf("\n");
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	
	scanf("%d",&T);
	for(int testcase=1;testcase<=T;testcase++) {
		memset(a,0,sizeof a);
		scanf("%d%d",&n,&m);
		int endx=0,endy=0;
		LL ans=0;
		for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) {
				scanf("%d",&a[i][j]);
				if(a[i][j]) endx=i,endy=j;
			}
				
		
		int cur=0,lt,state;
		LL w;
		memset(h[cur],-1,sizeof h[cur]);
		cnt[cur]=0;
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
					
					// can't pass
					if(!a[i][j]) {
						if(x==0 && y==0)
							insert(cur,state,w);
					}
					// end in this
					else if(i==endx && j==endy) {
						if(x==1 && y==2) 
							ans+=w;
					} 
					
					// A. x==0 && y==0
					else if(x==0 && y==0) {
						if(a[i+1][j] && a[i][j+1]) 
							insert(cur,state+make(j-1,1)+make(j,2),w);
					}
					
					// B. x==1,2 && y==0
					else if(x && y==0) {
						if(a[i+1][j]) insert(cur,state,w);
						if(a[i][j+1]) insert(cur,state-make(j-1,x)+make(j,x),w);
					}
					
					// C. x==0 && y==1,2
					else if(x==0 && y) {
						if(a[i+1][j]) insert(cur,state-make(j,y)+make(j-1,y),w);
						if(a[i][j+1]) insert(cur,state,w);
					}
					
					// D. x==1 && y==2; 
					else if(x==1 && y==2) {
						// a road end in this coin;
						insert(cur,state-make(j-1,1)-make(j,2),w);
					}
					
					// E. x==2 && y==1;
					else if(x==2 && y==1) {
						// tail ans head , no need to change!
						insert(cur,state-make(j-1,2)-make(j,1),w);
					}
					
					// F. x==1 && y==1;
					else if(x==1 && y==1) {
						z=find(state,j,2,1);
						insert(cur,state-make(z,2)+make(z,1)-make(j-1,1)-make(j,1),w);
					}
					
					// G. x==2 && y==2;
					else if(x==2 && y==2) {
						z=find(state,j-1,1,-1);
						insert(cur,state-make(z,1)+make(z,2)-make(j-1,2)-make(j,2),w);
					}
				}
			}
		}
		
		printf("Case %d: There are %lld ways to eat the trees.\n",testcase,ans);
	}
	return 0;
}

