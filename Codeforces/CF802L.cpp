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
typedef unsigned long long ULL;
typedef pair<LL,LL> PLL;

const int N=2e5+5;
const LL MOD=1e9+7;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x=(x%MOD+MOD)%MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

int one[N],idx;
int ver[N],Next[N];
LL edge[N];
inline void AddEdge(int a,int b,LL c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int n;
PLL f[N];

// E(x) ��ʾ�� x �ߵ�Ҷ�ӽڵ������������ 
// E(x)=f[x].first*E(fa(x))+f[x].second

void dp(int x,int fa,int cost)
{
	LL suma=0,sumb=cost,deg=0;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i]; deg++; // father Ҳ�����ĳ��ȡ� 
		if(y==fa) continue;
		dp(y,x,edge[i]);
		suma+=f[y].first;
		sumb+=f[y].second+edge[i];
	}
	suma%=MOD,sumb%=MOD; // ע��ȡģ������ 1e9 �����������п��ܱ� ll; 
	if(deg==1 && fa) f[x]=PLL(0,0); // Ҷ�ӽڵ�ͣס��,ע��Ҫ���е�����Ϊ 1 �ĸ��ڵ㡣 
	else {
		LL inver=power(deg-suma,MOD-2,MOD); 
		f[x]=PLL(inver,inver*sumb%MOD);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	LL z;
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%lld",&x,&y,&z); 
		AddEdge(++x,++y,z); AddEdge(y,x,z);
	}
	
	dp(1,0,0);
	printf("%lld\n",f[1].second);
	return 0;
}

