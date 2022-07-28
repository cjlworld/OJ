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

const int N=2e5+5;

struct Edges
{
	int u,v,w;
	inline bool operator<(const Edges& t) const
	{
		return w>t.w;
	}
}e[N];

int par[N],d[N]; // d[]=0 ��ʾ���� d[]=1 ��ʾ������ �� 
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) 
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+m+1);
	for(i=1;i<=n;i++) par[i]=i;
	
	LL ans=0;
	for(i=1;i<=m;i++) {
		x=Find(e[i].u); y=Find(e[i].v);
		if(x!=y && !(d[x]&d[y])) // �����������ǻ�������
			par[x]=y,d[y]=(d[x]|d[y]),ans+=e[i].w;
		else if(x==y && !d[x]) ans+=e[i].w,d[x]=1; // һ�������һ�û������� 
	}
	printf("%lld\n",ans);
	return 0;
}

