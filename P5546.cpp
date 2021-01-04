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

const int N=1e5+5;

int n,m;
char a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	int i,k,num;
	m=130;
	memset(c,0,sizeof c);
	
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
		x[sa[1]]=1,num=1;
		for(i=2;i<=n;i++) 
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num);
		m=num;
		if(m==n) break;
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
}

void get_ht()
{
	for(int i=1,j,k=0;i<=n;i++) {
		if(rk[i]==1) continue;
		if(k) k--;
		j=sa[rk[i]-1];
		while(i+k<=n && j+k<=n && a[i+k]==a[j+k]) k++;
		ht[rk[i]]=k;
	}
}

int cnt;
int b[N];
char s[N];
int q[N],c[N],cur;
int ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	int len;
	scanf("%d",&cnt);
	for(i=1;i<=cnt;i++) {
		scanf("%s",s+1);
		len=strlen(s+1);
		for(j=1;j<=len;j++)	
			a[n+j]=s[j],b[n+j]=i;
		n+=len;
		a[++n]='0'+i;
	}
	
	get_sa(),get_ht();
	
	int head=1,tail=0,hh=0,tt=0;
	for(head=1;head<=n;head++) {
		while(cur<cnt && tail<=n) {
			tail++;
			if(b[sa[tail]] && c[b[sa[tail]]]==0) cur++;
			c[b[sa[tail]]]++;
			
			while(hh<=tt && ht[q[tt]]>=ht[tail]) tt--;
			q[++tt]=tail;
		}
		
		if(cur==cnt) {
			if(q[hh]==head) ans=max(ans,ht[q[hh+1]]);
			else ans=max(ans,ht[q[hh]]);
		}
		
		if(b[sa[head]] && c[b[sa[head]]]==1) cur--;
		c[b[sa[head]]]--;
		if(q[hh]==head) hh++;
	}
	
	printf("%d\n",ans);
	return 0;
}

