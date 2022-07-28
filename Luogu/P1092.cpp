#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=26+6;
int a[4][N]; 
char c[N];
int g[N]; // g[i] = { a num | char('A'+i-1) stand for }
bool vis[N];
int n;
bool check()
{
	int i,up=0;
	int x,y,z;
	for(i=n;i>=1;i--) {
		x=g[a[1][i]]; y=g[a[2][i]]; z=g[a[3][i]];
		if(g[a[1][i]]!=-1&&g[a[2][i]]!=-1&&g[a[3][i]]!=-1) {
			if(up==-1) {
				if((x+y+1)%n!=z&&(x+y)%n!=z) return false;
				if(i==1&&x+y>=n) return false;
				if((x+y+1)/n==(x+y)/n) 
					up=(x+y+1)/n;
				else up=-1;
			}
			else {
				if((x+y+up)%n!=z) return false;
				up=(x+y+up)/n;
			}
		}
		else up=-1;
	}
	return true;
}
int s[N],tot=0;
void dfs(int step)
{
	if(step==n+1) {
		for(int i=1;i<=n;i++) 
			printf("%d ",g[i]);
		exit(0);
	}
	for(int i=0;i<=n-1;i++) {
		if(vis[i]) continue;
		g[s[step]]=i;
		vis[i]=true;
		if(check()) dfs(step+1);
		g[s[step]]=-1;
		vis[i]=false;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n;
	for(i=1;i<=3;i++) {
	    scanf("%s",c+1);
	    for(j=1;j<=n;j++) 
	        a[i][j]=c[j]-('A'-1);
	}
	memset(vis,0,sizeof vis);
	for(i=n;i>=1;i--) 
		for(j=1;j<=3;j++) 
			if(!vis[a[j][i]]) 
				vis[a[j][i]]=true,s[++tot]=a[j][i];
	memset(vis,0,sizeof vis);
	memset(g,-1,sizeof g);
	dfs(1);
	return 0;
}
