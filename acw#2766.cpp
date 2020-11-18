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

int n,m;
char s[N];
int sa[N],rk[N],ht[N];
// sa[i] 表示排名为i的后缀是 sa[i] 
void get_sa()
{
	static int x[N],y[N],c[N];
	int i,k,num;
	memset(c,0,sizeof c);
	for(i=1;i<=n;i++) c[x[i]=s[i]]++;
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
		for(i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(i=2;i<=n;i++) 
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num;
		if(num==n) break;
		m=num;
	} 
	for(i=1;i<=n;i++) rk[sa[i]]=i;
//	for(i=1;i<=n;i++) printf("%d ",sa[i]);
//	printf("\n");
}

void get_ht()
{
	int i,j,k=0;
	// dim h[i]=height[rk[i]]
	// h[i] >= h[i-1]-1;
	for(i=1;i<=n;i++) {
		if(rk[i]==1) continue;
		if(k) k--;
		j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) k++;
		ht[rk[i]]=k; 
	}
//	for(i=1;i<=n;i++) printf("%d ",ht[i]);
//	printf("\n");	
}

int pl[N],pr[N]; // ht[] 左边和右边第一个更小的数。 

void calc(int a[],int p[])
{
	static int stk[N],top;
	memset(stk,0,sizeof stk);
	top=0,stk[top]=1;

	for(int i=2;i<=n;i++) {
		while(top>=0&&a[stk[top]]>=a[i]) top--;
		p[i]=stk[top];
		stk[++top]=i;
	}
}
LL ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%s",s+1);
	n=strlen(s+1),m=122;
	get_sa(),get_ht();
	
	calc(ht,pl);
	reverse(ht+2,ht+n+1);
	calc(ht,pr);
	reverse(ht+2,ht+n+1);
	reverse(pr+2,pr+n+1);
	for(i=2;i<=n;i++) pr[i]=n+2-pr[i];
//	for(i=1;i<=n;i++) printf("%d ",pr[i]);
//	printf("\n");	
	for(i=2;i<=n;i++) {
		if(pr[i]-pl[i]<=1) continue;
		ans=max(ans,(LL)(pr[i]-pl[i])*(LL)ht[i]);
	}
	printf("%lld\n",ans);
	return 0;
}

