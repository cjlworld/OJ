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

const int N=2e5+5,n=26*26;

inline int id(char a,char b) { return (a-'a')*26+(b-'a'); }

int one[n],idx;
int ver[N],Next[N],edge[N];
inline void AddEdge(int a,int b,int c) 
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int m;

double dis[n];
bool vis[n]; // 维护在 dfs 栈里的点。

bool spfa(int x,const double& t)
{
	if(vis[x]) return true; // 找到力
	vis[x]=true;
	for(int i=one[x];~i;i=Next[i]) {
		int y=ver[i]; double z=t-edge[i];
		if(dis[y]>dis[x]+z) {
			dis[y]=dis[x]+z;
			if(spfa(y,t)) return true;
		}
	}
	vis[x]=false;
	return false;
} 

bool check(const double& t)
{	
	for(int i=0;i<n;i++) dis[i]=0; // 超级源点 
	memset(vis,false,sizeof vis);
		
	for(int i=0;i<n;i++) 
		if(~one[i] && spfa(i,t)) return true; 
	return false; 
}

char str[N];

int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d",&m),m) {
		memset(one,-1,sizeof one); idx=0;
		for(int i=1,x,y,z;i<=m;i++) {
			scanf("%s",str);
			z=strlen(str); x=id(str[0],str[1]); y=id(str[z-2],str[z-1]); 
			AddEdge(x,y,z); 
		}

		if(!check(0)) {
			puts("No solution");
			continue;
		}
		
		double L=0,R=1001,mid;
		while(L+0.01<R) {
			mid=(L+R)/2;
			if(check(mid)) L=mid;
			else R=mid;
		}
		printf("%.6lf\n",L);
	}
	return 0;
}

