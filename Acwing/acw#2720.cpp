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

const int N=5e5+5,INF=0x3f3f3f3f;

int n1,n2,n,m;
int sa[N],rk[N];
LL ht[N];
char a[N],str[N];

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

struct Node
{
	int l,r;
	LL val;
	Node(int l,int r,LL val) :
		l(l),r(r),val(val) {}
}; // 表示 sa[l,r] 中 b 串的与当前点的 lcp 都为 val; 
stack<Node> S;
LL cur,ans;

int s[N]; // 前缀和，用于快速得出 [l,r] 有多少个属于 b 串。 

int main()
{
//	freopen("1.in","r",stdin);
	int i;

	scanf("%s",str+1);
	n1=strlen(str+1);
	for(i=1;str[i];i++) a[++n]=str[i];
	a[++n]='#';
	scanf("%s",str+1);
	n2=strlen(str+1);
	for(i=1;str[i];i++) a[++n]=str[i];
	get_sa(); get_ht();
	for(i=1;i<=n;i++) s[i]=s[i-1]+(sa[i]>n1+1);
	
	while(S.size()) S.pop();
	cur=0;
	S.push(Node(0,0,-INF)); // 加入哨兵，不用特判边界条件。 
	for(i=3;i<=n;i++) { // '#' 的 ASCII 较小，会在第一个。 
		// 加入 ht[i]; 
		while(S.size()) {
			Node u=S.top();
			if(u.val<ht[i]) break;
			cur-=(s[u.r]-s[u.l-1])*u.val;
			S.pop();
		}
		int l=S.top().r+1;
		S.push(Node(l,i-1,ht[i]));
		cur+=(s[i-1]-s[l-1])*ht[i];
		
		// a 串需要计算贡献。
		if(sa[i]<=n1) ans+=cur;
	}
	
	// 倒着再来一遍。 
	while(S.size()) S.pop();
	cur=0;
	S.push(Node(n+1,n+1,-INF));
	
	for(i=n;i>=3;i--) {
		if(sa[i]<=n1) ans+=cur;
		
		// 加入 ht[i]; 
		while(S.size()) {
			Node u=S.top();
			if(u.val<ht[i]) break;
			cur-=(s[u.r]-s[u.l-1])*u.val;
			S.pop();
		}
		int r=S.top().l-1;
		S.push(Node(i,r,ht[i]));
		cur+=(s[r]-s[i-1])*ht[i];
	}
	
	printf("%lld\n",ans);
	return 0;
}

