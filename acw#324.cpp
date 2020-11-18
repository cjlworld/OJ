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
#include<sstream>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=456,INF=1e9+5;

int one[N],idx;
int Next[N],ver[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

map<string,int> mp;
int id;
int n,m;
int f[N][N],a[N],siz[N],deg[N];
int ans;

void Dp(int x,int fa)
{
	int i,j,k,y;
	f[x][0]=0,siz[x]=1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp(y,x);
		
		siz[x]+=siz[y];
		for(k=siz[x];k>=0;k--) 
			for(j=1;j<=min(siz[y],k);j++) 
				f[x][k]=min(f[x][k],f[x][k-j]+f[y][j]);
	}
	f[x][siz[x]]=a[x];
//	for(j=0;j<=siz[x];j++) 
//		printf("f[%d][%d] = %d\n",x,j,f[x][j]);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	stringstream ssin;
	string str,co;
	while(getline(cin,str)) {
		if(str[0]=='#') break;
		memset(f,0x3f,sizeof f);
		memset(deg,0,sizeof deg);
		memset(one,0,sizeof one);
		idx=0;
		mp.clear(),id=0;
		
		ssin.clear();
		ssin.str(str);
		ssin>>n>>m;
		for(i=1;i<=n;i++) {
			getline(cin,str);
			ssin.clear(),ssin.str(str);
			
			ssin>>co;
			if(!mp.count(co)) x=mp[co]=++id;//,cout<<co<<" : "<<id<<endl;
			else x=mp[co];
			
			ssin>>a[i];
			while(ssin>>co) {
				if(!mp.count(co)) y=mp[co]=++id;//,cout<<co<<" : "<<id<<endl;
				else y=mp[co];
				
				AddEdge(x,y);
				deg[y]++;
			}
		}
		for(i=1;i<=n;i++) 
			if(!deg[i]) AddEdge(0,i);
		ans=a[0]=INF;
		Dp(0,0);
		for(i=m;i<=n;i++) 
			ans=min(ans,f[0][i]);
		printf("%d\n",ans);
 	}
	return 0;
}

