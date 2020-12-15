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

const int N=21,M=300,S=(1<<21)+5,INF=0x3f3f3f3f;

int dis[S];
bool vis[S];

int T,n,m;
int b1[M],b2[M],f1[M],f2[M],w[M];

queue<int> q;
void spfa()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	
	int i;
	int x,y;
	
	dis[(1<<n)-1]=0;
	q.push((1<<n)-1);
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=1;i<=m;i++) {
			if((x&b1[i])^b1[i]||(x&b2[i])) continue;
			y=(x&f1[i]);
			y|=f2[i];
			
			if(dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				if(!vis[y]) 
					q.push(y),vis[y]=true;
			}
		}
	}
}

int main()
{
	int i,j;
	char str[30];
	
	while(scanf("%d%d",&n,&m),n||m) {
		memset(f1,0,sizeof f1);
		memset(f2,0,sizeof f2);
		memset(b1,0,sizeof b1);
		memset(b2,0,sizeof b2);
		
		for(i=1;i<=m;i++) {
			scanf("%d",&w[i]);
			
			scanf("%s",str);
			for(j=0;j<n;j++) {
				if(str[j]=='+') b1[i]+=(1<<j);
				else if(str[j]=='-') b2[i]+=(1<<j);
			}	
			
			scanf("%s",str);
			for(j=0;j<n;j++) {
				if(str[j]=='-') f1[i]+=(1<<j);
				else if(str[j]=='+') f2[i]+=(1<<j);
			}
			f1[i]^=((1<<n)-1);
		}
		spfa();
		
		printf("Product %d\n",++T);
		if(dis[0]==INF) printf("Bugs cannot be fixed.\n");
		else printf("Fastest sequence takes %d seconds.\n",dis[0]);
		printf("\n");
	}
	
	return 0;
}

