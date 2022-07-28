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

const int N=1e5+5;

int n,m;
int a[N];
int sa[N],rk[N],ht[N];

void get_sa()
{
	static int x[N],y[N],c[N];
	int i,k,num;
	m=N-1;
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
		x[sa[1]]=1,m=1;
		for(i=2;i<=n;i++) 
			x[sa[i]]=((y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? m : ++m);
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

int st[N][20];
int rmq(int l,int r)
{
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}

vector<int> nums;
set<int> S;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++)
		a[i]=(upper_bound(nums.begin(),nums.end(),a[i])-nums.begin());
	
	reverse(a+1,a+n+1);
	get_sa(),get_ht();
	
	for(i=1;i<=n;i++) st[i][0]=ht[i];
	for(j=1;(1<<j)<=n;j++) 
		for(i=1;i+(1<<j)-1<=n;i++) 
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);	
	
	LL ans=0;
	S.insert(-1);
	for(i=n,j=1;i>=1;i--,j++) {
		// add the char in turn ;
		ans+=j;
		x=*(--S.lower_bound(rk[i]));
		
		if(rk[i]>*(--S.end())) y=-1;
		else y=*S.upper_bound(rk[i]);
		
		if(~x && ~y) ans+=rmq(x+1,y);
		if(~x) ans-=rmq(x+1,rk[i]);
		if(~y) ans-=rmq(rk[i]+1,y);
		
		printf("%lld\n",ans);
		S.insert(rk[i]);
	}
	
	return 0;
}

