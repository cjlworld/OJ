#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	bool sign=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
const int N=1e5+5;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
queue< pair<int,int> > Q;
int dis[N][2];
bool vis[N][2];
inline void spfa(int st)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(Q.size()) Q.pop();
	int i,j;
	int x,y,z;
	dis[st][0]=0;
	vis[st][0]=true;
	Q.push(pair<int,int>(st,0));
	while(Q.size()) {
		x=Q.front().first; y=Q.front().second;
		Q.pop();
		vis[x][y]=false;
		for(i=one[x];i>0;i=Next[i]) {
			z=ver[i];
			if(dis[z][y^1]>dis[x][y]+1) {
				dis[z][y^1]=dis[x][y]+1;
				if(!vis[z][y^1]) {
					vis[z][y^1]=true;
					Q.push(pair<int,int>(z,y^1));
				}
			}
		}
	}
	return;
}
void dfs(int x)
{
    vis[x][0]=true;
    for(int i=one[x];i>0;i=Next[i]) 
        if(!vis[ver[i]][0]) 
            dfs(ver[i]);
    return;
}
int n,m,q;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	read(n); read(m); read(q);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	spfa(1);
	memset(vis,0,sizeof vis);
	dfs(1);
	int cnt=0;
	for(i=1;i<=n;i++) 
	    if(vis[i][0]||vis[i][1]) 
	        cnt++;
//	cout<<cnt<<endl;
	for(i=1;i<=q;i++) {
		read(x); read(y);
		if(dis[x][y&1]>y||cnt==1) puts("No");
		else puts("Yes");
	}
	return 0;
}
