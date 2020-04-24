#include<bits/stdc++.h>
using namespace std;
const int N=50000+5;
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
void update(int now)
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
void edit(int now,int x,int y)
{
	if(r(now)<x||l(now)>x) 
		return;
	if(l(now)==r(now)&&l(now)==x) {
		sl(now)=y;
		sm(now)=y;
		sr(now)=y;
		sum(now)=y;
		return;
	}
	edit(lc,x,y);
	edit(rc,x,y);
	update(now);
	return;
} 
node nul={0,0,0,0,0,0};
bool operator==(const node &a,const node &b)
{
	if(a.sl==b.sl&&a.sm==b.sm&&a.sr==b.sr&&a.sum==b.sum&&a.l==b.l&&a.r==b.r)
		return true;
	return false;
}
node query(int now,int x,int y)
{
	if(r(now)<x||l(now)>y)
		return nul;
	if(x<=l(now)&&y>=r(now)) //include entirely
		return t[now];
	node c,a,b;
	a=query(lc,x,y);
	b=query(rc,x,y);
	if(a==nul) c=b;
	else if(b==nul) c=a;
	else {
		c.sum=a.sum+b.sum;
		c.sl=max(a.sl,a.sum+b.sl);
		c.sr=max(b.sr,b.sum+a.sr);
		c.sm=max(a.sm,b.sm);
		c.sm=max(c.sm,a.sr+b.sl);
	}
	return c;
}
void print()
{
	int now;
	for(int i=1;i<=3*n;i++) {
		if(l(i)==0) continue;
		printf("%d~%d : %d %d %d  %d\n",l(i),r(i),sl(i),sm(i),sr(i),sum(i));
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%d",&ina[i]);
	build(1,1,n);
	scanf("%d",&m);
	int xx,yy;
	int opt;
//	print();
	while(m--) {
		scanf("%d%d%d",&opt,&xx,&yy);
		if(opt==0) edit(1,xx,yy);
		else printf("%d\n",query(1,xx,yy).sm);
	}
	return 0;
}

