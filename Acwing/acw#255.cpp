// AcWing 255
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
struct Bits
{
	int c[N];
	inline int lowbit(int x) { return x&(-x); }
	inline void Update(int x,int y) 
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	inline int Sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

struct Query
{
	int id,l,r,k;
}q[N],wl[N],wr[N];
int ans[N];

void solve(int l,int r,int ql,int qr) // 答案在[l,r]中，操作序列为[ql,qr]
{
	if(ql>qr) return;
	if(l==r) {
		for(int i=ql;i<=qr;i++) 
			if(q[i].id) ans[q[i].id]=l;
		return;
	}
	
	int mid=(l+r)>>1,i,j,t,lc=0,rc=0;
	
	for(i=ql;i<=qr;i++) {
		if(!q[i].id) { // insert
			if(q[i].k<=mid) C.Update(q[i].l,1),wl[++lc]=q[i];
			else wr[++rc]=q[i];
		} // 注意这里操作的顺序一定是所有插入都做完了才有询问。
		// 询问操作在任意时候都是在插入之前。 
		else { // Query
			t=C.Sum(q[i].r)-C.Sum(q[i].l-1);
			if(q[i].k<=t) // 在左边子树。
				wl[++lc]=q[i];
			else q[i].k-=t,wr[++rc]=q[i]; // 更新排名为在右边子树的排名。 
		}
	}
	
	for(i=ql;i<=qr && !q[i].id;i++) // 还原。 
		if(q[i].k<=mid) C.Update(q[i].l,-1);
	
	for(i=ql,j=1;j<=lc;j++,i++) q[i]=wl[j];
	for(j=1;j<=rc;j++,i++) q[i]=wr[j];
	
	solve(l,mid,ql,ql+lc-1),solve(mid+1,r,ql+lc,qr);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d%d",&n,&m);
	
	for(i=1;i<=n;i++) {
		scanf("%d",&q[i].k);
		q[i].l=i,q[i].id=0;
	}
	for(j=1;j<=m;j++,i++) {
		scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
		q[i].id=j;
	}
	
	solve(-1e9,1e9,1,n+m);
	for(i=1;i<=m;i++)	
		printf("%d\n",ans[i]);
	return 0;
}

