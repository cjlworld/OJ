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

const int N=1e6+5;

int n,times;
int a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	int m=N-1;
	int i,k,num;
	for(i=1;i<=m;i++) c[i]=0;
	for(i=1;i<=n;i++) c[x[i]=a[i]]++;
	for(i=1;i<=m;i++) c[i]+=c[i-1];
	for(i=n;i>=1;i--) sa[c[x[i]]--]=i;
	
	for(k=1;k<=n;k<<=1) {
		num=0;
		for(i=n-k+1;i<=n;i++) y[++num]=i;
		for(i=1;i<=n;i++) 
			if(sa[i]>k) y[++num]=sa[i]-k;
		
		for(i=1;i<=m;i++) c[i]=0;
		for(i=1;i<=n;i++) c[x[i]]++;
		for(i=1;i<=m;i++) c[i]+=c[i-1];
		for(i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		
		swap(x,y);
		x[sa[1]]=m=1;
		for(i=2;i<=n;i++) 
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? m : ++m);
		if(m==n) break;
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
}

void get_ht()
{
	for(int i=1,j,k=1;i<=n;i++) {
		if(rk[i]==1) continue;
		if(k) k--;
		j=sa[rk[i]-1];
		while(i+k<=n && j+k<=n && a[i+k]==a[j+k]) k++;
		ht[rk[i]]=k;
	}
}

int st[N][20];
inline int rmq(int l,int r)
{
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d%d",&n,&times);
	for(i=1;i<=n;i++) scanf("%d",&a[i]),a[i]++;
	get_sa(); get_ht();
	
	for(i=1;i<=n;i++) st[i][0]=ht[i];
	for(j=1;(1<<j)<=n;j++) 
		for(i=1;i+(1<<j)-1<=n;i++) 
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	
	int ans=0;
	for(i=1;i<=n-times+1;i++) 
		ans=max(ans,rmq(i+1,i+times-1));
	printf("%d\n",ans);
	return 0;
}

