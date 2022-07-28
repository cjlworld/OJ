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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

// A -> 1 , B -> 2 , C -> 3 , x -> 0;

const int N=2e5+5,M=2e6+5;

int one[N],idx;
int ver[M],Next[M];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
//	printf("Edge ( %d -> %d )\n",a,b);
}

struct Edges
{
	int i,hi,j,hj;
}e[N];

vector<int> vx;

int n,m,d;
char str[N];
int a[N];

inline int get(int i,int hi)
{
	if(a[i]==1) return n*(hi==3)+i;
	else if(a[i]==2) return n*(hi==3)+i;
	else return n*(hi==2)+i; 
}
inline int get_other(int i,int hi)
{
	for(int j=1;j<=3;j++) {
		if(a[i]==j || hi==j) continue;
		else return j;
	}
	return -1;
}

int dfn[N],low[N],times;
int col[N],all;
stack<int> S;

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!col[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]) {
		all++;
		while(S.size() && S.top()!=x) 
			col[S.top()]=all,S.pop();
		col[x]=all; S.pop();
	}
}

void check()
{
	memset(one,-1,sizeof one); idx=0;
	
	int i,j;
//	printf("now in check a[] = {");
//	for(i=1;i<=n;i++) printf("%d,",a[i]);
//	printf("}\n");
	for(i=1;i<=m;i++) {
		Edges& t=e[i];
		if(a[t.i]==t.hi) continue;
		else if(a[t.j]==t.hj) 
			AddEdge(get(t.i,t.hi),get(t.i,get_other(t.i,t.hi)));
		else {
			AddEdge(get(t.i,t.hi),get(t.j,t.hj));
			AddEdge(get(t.j,get_other(t.j,t.hj)),get(t.i,get_other(t.i,t.hi)));
		}
	}
	
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(col,0,sizeof col);
	while(S.size()) S.pop();
	all=times=0;
	
	for(i=1;i<=2*n;i++) 
		if(!dfn[i]) tarjan(i);
	for(i=1;i<=n;i++) 
		if(col[i]==col[i+n]) 
			return;
	for(i=1;i<=n;i++) {
		int w1=0,w2=0;
		for(j=1;j<=3;j++) {
			if(a[i]==j) continue;
			else if(!w1) w1=j;
			else w2=j;
		}
		if(col[i]<col[i+n]) putchar('A'+w1-1);
		else putchar('A'+w2-1);
	}
	exit(0);
}

void dfs(int u)
{
	if(u==d) return check();
	for(int i=1;i<=2;i++) {
		a[vx[u]]=i;
		dfs(u+1);
		a[vx[u]]=0;
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	char opt[2];
	scanf("%d%d",&n,&d);
	scanf("%s",str+1);
	for(i=1;i<=n;i++) {
		if(str[i]=='x') a[i]=0,vx.push_back(i);
		else a[i]=str[i]-'a'+1;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d%s",&e[i].i,opt); e[i].hi=*opt-'A'+1;
		scanf("%d%s",&e[i].j,opt); e[i].hj=*opt-'A'+1;
		
//		printf("rule ( %d with %d -> %d with %d )\n",e[i].i,e[i].hi,e[i].j,e[i].hj);
	}
		
	dfs(0);
	puts("-1");
	return 0;
}

