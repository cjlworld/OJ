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

int n,m;
char a[N];
int sa[N],rk[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	m=131;
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
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]] && y[sa[i-1]+k]==y[sa[i]+k]) ? m : ++m);
		if(m==n) break;
	} 
	for(i=1;i<=n;i++) rk[sa[i]]=i;
}

int cnt;
char b[200][200];

bool contain(char *a,char *b)
{
//	printf("contain %s , %s ",a,b);
	int i;
	for(i=0;a[i] && b[i];i++) 
		if(a[i]!=b[i]) break;
//	if(b[i]) printf("No\n");
//	else printf("Yes\n");
	if(b[i]) return false;
	else return true;
}

bool cmp(char *a,char *b) // <
{
	for(int i=0;a[i] || b[i];i++) {
		if(!a[i]) return true;
		if(!b[i]) return false;
		if(a[i]!=b[i]) return (a[i]<b[i]);
	}
	return false; //=
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	while(scanf("%d",&cnt),cnt) {
		for(i=1;i<=cnt;i++) 
			scanf("%s",b[i]+1);
		scanf("%s",a+1);
		n=strlen(a+1);
		get_sa();
		int mx=0; vector<int> ans;
		
		for(i=1;i<=cnt;i++) {
			int times=0;
			int L=0,R=n+1,mid;
			while(L+1<R) {
				mid=(L+R)>>1;
				if(cmp(a+sa[mid],b[i]+1)) L=mid; //<
				else R=mid; // >=
			}

			R=L;
			for(int k=log2(n-L+1);k>=0;k--) 
				if(R+(1<<k)<=n && contain(a+sa[R+(1<<k)],b[i]+1)) 
					R+=(1<<k);
			times=R-L;
//			int times=0;
//			for(int j=1;j<=n;j++) 
//				if(contain(a+j,b[i]+1)) times++;
			
			if(times>mx) ans.clear(),ans.push_back(i),mx=times;
			else if(times==mx) ans.push_back(i);
		}	
		
		printf("%d\n",mx);
		for(i=0;i<(int)ans.size();i++) 
			printf("%s\n",b[ans[i]]+1);
	}
	return 0;
}

