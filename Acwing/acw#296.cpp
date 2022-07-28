#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=2e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int n,s,t;

struct Len
{
	int a,b;
	LL c;
}a[N];

vector<int> v[N];

LL cmin[4*N];
#define lc (now<<1)
#define rc (now<<1|1)

void Update(int now,int pos,LL key,int l,int r)
{
	if(l==r) return cmin[now]=key,void();
	int mid=(l+r)>>1;
	if(pos<=mid) Update(lc,pos,key,l,mid);
	else Update(rc,pos,key,mid+1,r);
	cmin[now]=min(cmin[lc],cmin[rc]);
//	if(cmin[now]!=0) printf("%d %d : %lld\n",l,r,cmin[now]);
}

LL query(int now,int x,int y,int l,int r)
{
	if(x<=l&&r<=y) return cmin[now];
	int mid=(l+r)>>1;
	LL res=INF;
	if(x<=mid) res=min(res,query(lc,x,y,l,mid));
	if(y>=mid+1) res=min(res,query(rc,x,y,mid+1,r));
	return res;
}

LL f[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x;
	LL sum=0;
	scanf("%d%d%d",&n,&s,&t);
	s+=2,t+=2;
	for(i=1;i<=n;i++) {
		scanf("%d%d%lld",&a[i].a,&a[i].b,&a[i].c);
		a[i].a+=2,a[i].b+=2;
		v[a[i].b].push_back(i);
		sum+=a[i].c;
	}
	memset(cmin,0x3f,sizeof cmin);
	memset(f,0x3f,sizeof f);
	for(i=1;i<=s-1;i++) 
		Update(1,i,0,1,t);
	for(i=s;i<=t;i++) {
		for(j=0;j<(int)v[i].size();j++) {
			x=v[i][j];
//			if(x>n) printf("here");
			f[i]=min(f[i],query(1,a[x].a-1,i-1,1,t)+a[x].c);
//			cout<<a[x].a-1<<" "<<i-1<<" : "<<query(1,a[x].a-1,i-1,1,t)<<endl;
		}
		if(v[i].size()) Update(1,i,f[i],1,t);
//		if(f[i]<INF) printf("%d %lld\n",i,f[i]);
	}
	if(f[t]>sum) printf("-1\n");
	else printf("%lld\n",f[t]);
	return 0;
}

