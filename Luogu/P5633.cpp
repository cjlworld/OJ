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
typedef pair<int,int> PII;
typedef pair<LL,int> PLI;

const int N=5e5+5;

int n,m,s,need;

struct Edge
{
	int a,b;
	LL c;
}e[N],e1[N],e2[N];
int tot,tot1,tot2;

vector<int> G[N];

inline bool cmp(const Edge& x,const Edge& y)
{
	if(x.c!=y.c) return x.c<y.c;
	else return (x.a==s)+(x.b==s)>(y.a==s)+(y.b==s);
}

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

inline void MergeSort(Edge c[],Edge a[],Edge b[])
{
	tot=0;
	int i=1,j=1;
	while(i<=tot1 && j<=tot2) {
		if(cmp(a[i],b[j])) c[++tot]=a[i++];
		else c[++tot]=b[j++];
	}
	while(i<=tot1) c[++tot]=a[i++];
	while(j<=tot2) c[++tot]=b[j++];
}

PLI check(LL t)
{
	for(int i=1;i<=m;i++) e1[i].c-=t;
	MergeSort(e,e1,e2);
	PLI res(0,0);
	for(int i=1;i<=n;i++) par[i]=i;
	for(int i=1,cnt=0;i<=m && cnt<n-1;i++) {
		int x=Find(e[i].a),y=Find(e[i].b);
		if(x==y) continue;
		par[x]=y;
		res.first+=e[i].c;
		res.second+=(e[i].a==s)+(e[i].b==s);
		cnt++;
	}
	
	for(int i=1;i<=m;i++) e1[i].c+=t;
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%d%d%d",&n,&m,&s,&need);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=m;i++) {
		scanf("%d%d%lld",&e[i].a,&e[i].b,&e[i].c);
		G[e[i].a].push_back(e[i].b);
		G[e[i].b].push_back(e[i].a);
		if(e[i].a^s && e[i].b^s) 
			par[Find(e[i].a)]=Find(e[i].b),e2[++tot2]=e[i];
		else e1[++tot1]=e[i];
	}
	for(i=1;i<=n;i++) {
		sort(G[i].begin(),G[i].end());
		G[i].erase(unique(G[i].begin(),G[i].end()),G[i].end());
	}
	if((int)G[s].size()<need) return puts("Impossible")&0;
	int cnt=0;
	for(i=0;i<(int)G[s].size();i++) 
		if(Find(s)!=Find(G[s][i])) {
			cnt++;
			par[Find(s)]=Find(G[s][i]);
		}
	if(cnt>need) return puts("Impossible")&0;
	for(i=1;i<=n;i++) 
		if(Find(i)!=Find(1)) 
			return puts("Impossible")&0;
	// 先把其他部分连起来，若 s 加入 >need 条边才能使图连通，无解。
	// 否则一定有解。 
	
	sort(e1+1,e1+tot1+1,cmp);
	sort(e2+1,e2+tot2+1,cmp);	
	
	LL L=-1e7,R=1e7,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid).second>=need) R=mid;
		else L=mid;
	}
	
	printf("%lld\n",check(R).first+need*R);
	return 0;
}
