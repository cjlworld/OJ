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

const int N=4e6+5;

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
//	printf("Edge (%d , %d)\n",a,b);
}

int n;
struct Wedding
{
	int s,t,d;
}a[N];

inline bool insec(int l1,int r1,int l2,int r2)
{
	return !(l2>=r1 || l1>=r2);
}

stack<int> S;
int dfn[N],low[N],times;
int col[N],all;

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

inline void putime(int tim)
{
	printf("%02d:%02d",tim/60,tim%60);	
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,j;

	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		int s0,s1,t0,t1;
		scanf("%d:%d %d:%d %d",&s0,&s1,&t0,&t1,&a[i].d);
		a[i].s=s0*60+s1;
		a[i].t=t0*60+t1;
	}
	
	memset(one,-1,sizeof one);
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) {
			if(i==j) continue;
			if(insec(a[i].s,a[i].s+a[i].d,a[j].s,a[j].s+a[j].d)) AddEdge(i,j+n);
			if(insec(a[i].s,a[i].s+a[i].d,a[j].t-a[j].d,a[j].t)) AddEdge(i,j);
			if(insec(a[i].t-a[i].d,a[i].t,a[j].s,a[j].s+a[j].d)) AddEdge(i+n,j+n);
			if(insec(a[i].t-a[i].d,a[i].t,a[j].t-a[j].d,a[j].t)) AddEdge(i+n,j);
			// 会由 j 加入到 i 的对称的边，因此形成的图也具有对称性。 
		}
	
	for(i=1;i<=n*2;i++) 
		if(!dfn[i]) tarjan(i);
	for(i=1;i<=n;i++)
		if(col[i+n]==col[i])  // 在同一个强联通分量里。
			return puts("NO")&0;
	puts("YES");
	for(i=1;i<=n;i++) {
		if(col[i]<col[i+n]) putime(a[i].s),putchar(' '),putime(a[i].s+a[i].d),putchar('\n');
		else putime(a[i].t-a[i].d),putchar(' '),putime(a[i].t),putchar('\n');
	}
	return 0;
}

