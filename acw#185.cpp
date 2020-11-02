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

const int N=16;
int n;
struct State
{
	int a[7][9];
	State() { memset(a,0,sizeof a); }
	bool empty()
	{
		for(int i=1;i<=5;i++) 
			if(a[i][1]) return false;
		return true;
	}
	void pushfront()
	{
		int i,j,k;
		for(i=1;i<=5;i++) 
			for(j=2;j<=7;j++) 
				for(k=j;k>=2&&a[i][k]&&!a[i][k-1];k--) 
					swap(a[i][k],a[i][k-1]);		
	}
	void del(int x,int y)
	{
		int i,l,r;
		int val=a[x][y];
		
		for(l=y-1;l>=1&&a[x][l]==val;l--); l++;
		for(r=y+1;r<=7&&a[x][r]==val;r++); r--;
		if(r-l+1>=3) {
			for(i=l;i<=r;i++) 
				a[x][i]=0;
		}
		pushfront();
	}
	void scan(int x,int y)
	{
		int i,l,r;
		int val=a[x][y];
//		if(!val) cerr<<"here"<<endl;
		for(l=x-1;l>=1&&a[l][y]==val;l--); l++;
		for(r=x+1;r<=5&&a[r][y]==val;r++); r--;
		
		for(i=l;i<=r;i++) del(i,y);
		if(r-l+1>=3) {
			for(i=l;i<=r;i++) 
				a[i][y]=0;
		}
		pushfront();
	}
	void suit()
	{
		pushfront();
		int i,j;
		for(i=2;i<=4;i++) 
			for(j=1;j<=7;j++) 
				if(a[i][j]&&a[i][j]==a[i-1][j]&&a[i][j]==a[i+1][j])
					return scan(i,j),suit();
		for(i=1;i<=5;i++) 
			for(j=2;j<=6;j++) 
				if(a[i][j]&&a[i][j]==a[i][j+1]&&a[i][j]==a[i][j-1])
					return scan(i,j),suit();
	}
	void print()
	{
		int i,j;
		for(i=1;i<=5;i++) {
			for(j=1;j<=7;j++) {
				if(!a[i][j]) break;
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
		printf("/*********/\n");
	}
};

int path[N][3];
int cnt[N];

bool dfs(int step,State u)
{
	if(step==n+1) return u.empty();
	int i,j;
	
	memset(cnt,0,sizeof cnt);
	for(i=1;i<=5;i++) 
		for(j=1;j<=7;j++) 
			cnt[u.a[i][j]]++;
	for(i=1;i<=10;i++) 
		if(cnt[i]>0&&cnt[i]<3) return false;
	
	State nxt;
	for(i=1;i<=5;i++) 
		for(j=1;j<=7&&u.a[i][j];j++) {
			path[step][0]=i,path[step][1]=j;
			if(i<5) {
				path[step][2]=1;
				nxt=u;
				swap(nxt.a[i][j],nxt.a[i+1][j]);
				nxt.suit();
				if(dfs(step+1,nxt)) return true;
			}
			if(i==5||(i>1&&u.a[i-1][j]==0)) {
				path[step][2]=-1;
				nxt=u;
				swap(nxt.a[i][j],nxt.a[i-1][j]);
				nxt.suit();
				if(dfs(step+1,nxt)) return true;
			}
		}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,j,x;
	State s;
	cin>>n;
	for(i=1;i<=5;i++) {
		j=0;
		while(cin>>x,x) 
			s.a[i][++j]=x;
	}
	if(dfs(1,s)) {
		for(i=1;i<=n;i++)
			printf("%d %d %d\n",path[i][0]-1,path[i][1]-1,path[i][2]);
	}
	else printf("-1\n");
	return 0;
}

