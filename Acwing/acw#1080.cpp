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

const int N=1e6+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int one[N],idx;
int Next[2*N],ver[2*N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

LL f[N][2];
LL a[N];

void Dp(int x,int fa)
{
	f[x][1]=a[x]; f[x][0]=0;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
}

int n;
vector<PII> roots;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x;
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=n;i++) {
		scanf("%lld%d",&a[i],&x);
		if(Find(i)==Find(x)) 
			roots.push_back(PII(i,x));
		else AddEdge(x,i),par[Find(x)]=Find(i);
	}
	
	LL ans=0;
	for(i=0;i<(int)roots.size();i++) {
		PII u=roots[i];
		Dp(u.first,0);
		LL res=f[u.first][0];
		Dp(u.second,0);
		res=max(res,f[u.second][0]);
		ans+=res;
	}
	
	printf("%lld\n",ans);
	return 0;
}

