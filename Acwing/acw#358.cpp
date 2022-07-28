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

const int N=2e6+5;

int one[N],idx=1;
int ver[N],Next[N];
LL edge[N];
inline void AddEdge(int a,int b,LL c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

bool vis[N],ins[N]; // 有没有被访问过 / 是否在系统栈里。 
int fu[N];
LL fw[N];

bool isc[N];
vector<int> v[N];
int cnt;

void dfsCir(int x,int from)
{
	int i,k,y;
	vis[x]=ins[x]=true;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(i==(from^1)) continue;
		if(!vis[y]) fu[y]=x,fw[y]=edge[i],dfsCir(y,i);
		else if(ins[y]) {
			cnt++;
			fu[y]=x,fw[y]=edge[i];
			for(k=x;k^y;k=fu[k]) 
				v[cnt].push_back(k);
			v[cnt].push_back(y);
		}
	}
	ins[x]=false;
}

LL f[N];
LL ans,tmp;
void Dp(int x)
{
	vis[x]=true;
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]) continue;
		Dp(y);
		tmp=max(tmp,f[x]+edge[i]+f[y]);
		f[x]=max(f[x],edge[i]+f[y]);
	}
}

int q[N];
LL sum[N];
void deal(vector<int> &v)
{
	int len=v.size(),i;
	tmp=0;
	reverse(v.begin(),v.end());
	for(i=0;i<len;i++) vis[v[i]]=true;
	for(i=0;i<len;i++) Dp(v[i]);//,cout<<v[i]<<" ";
	for(i=0;i<len;i++) 
		v.push_back(v[i]);
	sum[0]=0;
	for(i=1;i<len+len;i++) 
		sum[i]=sum[i-1]+fw[v[i]];
	int hh=1,tt=0;
	for(i=0;i<len+len;i++) {
		while(hh<=tt && q[hh]+len-1<i) hh++;
		if(hh<=tt) tmp=max(tmp,f[v[q[hh]]]-sum[q[hh]]+sum[i]+f[v[i]]);
		while(hh<=tt && f[v[q[tt]]]-sum[q[tt]]<=f[v[i]]-sum[i]) tt--;
		q[++tt]=i;
	}
	ans+=tmp;
}
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int y;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d%lld",&y,&z);
		AddEdge(i,y,z),AddEdge(y,i,z);
	}
	
	for(i=1;i<=n;i++)
		if(!vis[i]) dfsCir(i,-1);
	memset(vis,0,sizeof vis);	
	for(i=1;i<=cnt;i++)
		deal(v[i]);
	cout<<ans<<endl;
	return 0;
}

