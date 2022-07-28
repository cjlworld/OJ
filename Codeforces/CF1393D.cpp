#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rint register int
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2056;
char a[N][N];
int f[N][N];
int n,m;
struct State
{
	int x,y;
	int size;
	State(int x,int y,int size) : x(x),y(y),size(size) {}
	State() {}
	inline bool check()
	{
		if(!(x+size<=n&&x-size>=1&&y+size<=m&&y-size>=1))
			return false;
		if(f[x-1][y-1]==f[x-1][y+1]&&f[x-1][y+1]==f[x+1][y-1]&&f[x+1][y-1]==f[x+1][y+1]&&a[x+1][y+1]==a[x][y])
			return true;
		return false;	
	} 
};
queue<State> q;
ULL ans=0;
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	scanf("%d%d",&n,&m);
	bool flag=true;
	for(i=1;i<=n;i++) {
		scanf("%s",a[i]+1);
		for(j=1;j<=m;j++) 
			if(a[i][j]!=a[1][1]) 
				flag=false;
	}
	if(flag) {
		for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) 	
				ans+=(ULL)min(min(i,n-i+1),min(j,m-j+1));
		cout<<ans;
		return 0;
	}
	while(q.size()>0) q.pop();
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) {
			q.push(State(i,j,1));
			ans++;
		}
	register State u;
	while(q.size()>0) {
		u=q.front(); q.pop();
		if(u.check()) q.push(State(u.x,u.y,u.size+1)),ans++,f[u.x][u.y]=u.size+1;
	}
	cout<<ans;
	return 0;
}
