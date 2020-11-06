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

const int N=1e6+5;
const ULL P=233333,NP=144177;
ULL NPC;
int n;
ULL a[N],f[N][2];
int lc[N],rc[N],siz[N];
int dep[N],h;

int ans;
void Dp(int x)
{
	ULL p1=0,p2=0;
	int s1=0,s2=0,d1=0,d2=0;
	if(~lc[x]) Dp(lc[x]),p1=f[lc[x]][0],s1=siz[lc[x]],d1=dep[lc[x]];
	if(~rc[x]) Dp(rc[x]),p2=f[rc[x]][1],s2=siz[rc[x]],d2=dep[rc[x]];
	if(p1==p2&&s1==s2&&d1==d2) ans=max(ans,siz[x]);
	
	f[x][0]=p1*s1*P+a[x]*NP+((~rc[x]) ? f[rc[x]][0] : 997)*NPC*d2;
	f[x][1]=p2*s2*P+a[x]*NP+((~lc[x]) ? f[lc[x]][1] : 997)*NPC*d1;
	
//	printf("%d : %llu %llu\n",x,f[x][0],f[x][1]);
}

void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	h=max(h,dep[x]);
	siz[x]=1;
	if(~lc[x]) dfs1(lc[x],x),siz[x]+=siz[lc[x]];
	if(~rc[x]) dfs1(rc[x],x),siz[x]+=siz[rc[x]];
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	srand((unsigned)time(0));
	NPC=(LL)rand()*rand();
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%llu",&a[i]);
	for(i=1;i<=n;i++) 
		scanf("%d%d",&lc[i],&rc[i]);
	dfs1(1,0);
	Dp(1);
	cout<<ans<<endl;
	return 0;
}
