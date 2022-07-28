#include<bits/stdc++.h>
#define rint register int 
using namespace std;
const int N=10000+5;
int ina[N];
int n,m;
struct node
{
	int l,r;
	int sl,sr,sm;
	int sum;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define sl(x) t[x].sl
	#define sr(x) t[x].sr
	#define sm(x) t[x].sm
	#define sum(x) t[x].sum
};
node t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
inline node merge(const node &a,const node &b)
{
	node c;
	c.sum=a.sum+b.sum;
	c.sl=max(a.sl,a.sum+b.sl);
	c.sr=max(b.sr,b.sum+a.sr);
	c.sm=max(a.sm,b.sm);
	c.sm=max(c.sm,a.sr+b.sl);
	return c;
}
inline void update(int now)
{
	sum(now)=sum(lc)+sum(rc);
	sl(now)=max(sl(lc),sum(lc)+sl(rc));
	sr(now)=max(sr(rc),sum(rc)+sr(lc));
	sm(now)=max(sm(lc),sm(rc));
	sm(now)=max(sm(now),sr(lc)+sl(rc));
	return;
}
void build(int now,int L,int R)
{
	l(now)=L;
	r(now)=R;
	if(L==R) {
		sl(now)=ina[L];
		sr(now)=ina[R];
		sm(now)=ina[L];
		sum(now)=ina[L];
		return;
	}
	int mid=(L+R)>>1;
	build(lc,L,mid);
	build(rc,mid+1,R);
	update(now);
	return;
}
node nul={0,0,0,0,0,0};
bool operator==(const node &a,const node &b)
{
	return (a.sl==b.sl&&a.sm==b.sm&&a.sr==b.sr&&a.sum==b.sum&&a.l==b.l&&a.r==b.r);
}
node query(int now,const int &x,const int &y)
{
	if(x>y) return nul;
	if(r(now)<x||l(now)>y)
		return nul;
	if(x<=l(now)&&y>=r(now)) //include entirely
		return t[now];
	node c,a,b;
	a=query(lc,x,y);
	b=query(rc,x,y);
	if(a==nul) c=b;
	else if(b==nul) c=a;
	else c=merge(a,b);
	return c;
}
int T;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x_1,x_2,y_1,y_2;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=1;i<=n;i++) 
			scanf("%d",&ina[i]);
		build(1,1,n);
		scanf("%d",&m);
		while(m--) {
			scanf("%d%d%d%d",&x_1,&x_2,&y_1,&y_2);
			if(x_2<y_1) printf("%d\n",query(1,x_1,x_2).sr+query(1,x_2+1,y_1-1).sum+query(1,y_1,y_2).sl);
			else 
				printf("%d\n",max(query(1,x_1,y_1-1).sr+query(1,y_1,y_2).sl,max(query(1,x_1,x_2).sr+query(1,x_2+1,y_2).sl,query(1,y_1,x_2).sm)));
		}
	}
	return 0;
}
