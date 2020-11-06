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

const int N=1e4+5;
int one[N],idx=1;
int ver[N],Next[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int dfn[N],low[N],times;
int all;
vector<int> dcc[N];
bool iscut[N];
stack<int> S;

void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	
	if(!fa&&!one[x]) {
		dcc[++all].push_back(x);
		S.pop();
		return;
	}
	
	int i,y,child=0;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			child++;
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) {
				if((fa==0&&child>1)||fa) iscut[x]=true;
				all++;
				while(S.top()!=y)
					dcc[all].push_back(S.top()),S.pop();
				dcc[all].push_back(y),S.pop();
				dcc[all].push_back(x);
			}
		}
		else if(y!=fa) 
			low[x]=min(low[x],dfn[y]);
	}
}

LL C(LL n,LL m)
{
	LL i,j,up=1,down=1;
	for(i=n,j=1;j<=m;j++,i--) 
		up*=i,down*=j;
	return up/down;
}

int n,m,T;
LL ans,cnt;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,sum,siz;
	while(scanf("%d",&m),m) {
		for(i=1;i<=all;i++)	
			dcc[i].clear();
		memset(dfn,0,sizeof dfn);
		memset(one,0,sizeof one); 
		memset(low,0,sizeof low);
		memset(iscut,0,sizeof iscut);
		while(S.size()) S.pop();
		n=times=all=ans=0,idx=1,cnt=1;
		
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			n=max(n,x),n=max(n,y);
			AddEdge(x,y),AddEdge(y,x);
		}
		for(i=1;i<=n;i++) 
			if(!dfn[i]) tarjan(i,0);
		
		for(i=1;i<=all;i++) {
			sum=0,siz=dcc[i].size();
			for(j=0;j<siz;j++) 
				if(iscut[dcc[i][j]]) sum++;
			if(sum==0) {
			    if(siz-sum==1&&n>1) ans+=1; 
				else if(siz-sum>=2) ans+=2,cnt*=C(siz-sum,2);
			}
			else if(sum==1) {
				if(siz-sum>=1) ans++,cnt*=C(siz-sum,1);  
			}
//			printf("%d %d %lld\n",siz,sum,cnt);
		}
		printf("Case %d: %lld %lld\n",++T,ans,cnt);
	}
	return 0;
}

