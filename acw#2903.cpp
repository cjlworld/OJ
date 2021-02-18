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

const int N=1e6+5,INF=0x3f3f3f3f;

int n,m;
char a[N];
int sa[N],rk[N];
LL ht[N];

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
		j=sa[rk[i]-1]; // 答案的最小值是从 rk[i-1] 继承来的，
					// 但我们是求 sa[rk[i]-1] 和 i 的 lcp 
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
}; // 表示 [l,r] 中都与当前位置 lcp 为 val; 

stack<Node> S; 
LL cur; // 当前栈中 sum{ (r-l+1)*val } 
LL ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%s",a+1);
	n=strlen(a+1);
	get_sa(); get_ht();

	S.push(Node(0,0,-INF));
	for(i=2;i<=n;i++) {
		while(S.size()) {
			Node u=S.top(); 
			if(u.val<ht[i]) break;
			cur-=(u.r-u.l+1)*u.val;
			S.pop();
		}
		int l=S.top().r+1;
		S.push(Node(l,i-1,ht[i]));
		cur+=(i-l)*ht[i];
		
		ans-=cur*2;
		ans+=(LL)((n-i+2)+n)*(i-1)/2+(LL)(i-1)*(n-i+1);
	}

	printf("%lld\n",ans);
	return 0;
}

//int st[N][20];
//	ans+=(LL)n*(n-1)*(n+1)/2;
//	for(i=1;i<=n;i++) st[i][0]=ht[i];
//	for(j=1;(1<<j)<=n;j++)
//		for(i=1;i+(1<<j)-1<=n;i++) 
//			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
