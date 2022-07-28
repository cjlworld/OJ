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

const int N=2e5+5;

int n,m;
char a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	int i,k,num;
	memset(c,0,sizeof c);
	m=130;
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

vector<int> v;
char ans[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,x;
	
	scanf("%s",a+1);
	n=strlen(a+1);
	for(i=n+1;i<=2*n;i++) 
		a[i]=a[i-n];
	n*=2;
	
	get_sa();
	for(i=1;i<=n/2;i++)
		v.push_back(rk[i]);
	sort(v.begin(),v.end());
	for(i=1;i<=n/2;i++) {
		x=lower_bound(v.begin(),v.end(),rk[i])-v.begin();
		ans[x]=a[i+n/2-1];
	}
	for(i=0;i<n;i++) putchar(ans[i]);
	return 0;
}

