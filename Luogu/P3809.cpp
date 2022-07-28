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
char a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	m=130;
	memset(c,0,sizeof c);
	int i,num,k;
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
		if(m==n) return; 
	}
	for(i=1;i<=n;i++) rk[sa[i]]=i;
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%s",a+1);
	n=strlen(a+1);
	get_sa();
	for(int i=1;i<=n;i++) 
		printf("%d ",sa[i]);
	printf("\n");
	return 0;
}

