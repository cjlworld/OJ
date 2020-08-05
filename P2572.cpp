#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
struct Node
{
	int l,r;
	int tag; // tag :: -1 ---> no ,0---> all 0 , 1---> all 1 , 2---> reverse 
	int sum; // Çø¼äºÍ 
	int sm[2],sl[2],sr[2];
	Node(int tag) : tag(tag) {}
	Node() {}
}t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
inline void Update(const int &now)
{
	t[now].sum=t[lc].sum+t[rc].sum;
	t[now].sm[1]=max(t[lc].sm[1],t[rc].sm[1]);
	t[now].sm[1]=max(t[now].sm[1],t[lc].sr[1]+t[rc].sl[1]);
	
	t[now].sl[1]=(t[lc].sum==t[lc].r-t[lc].l+1) ? t[lc].sum+t[rc].sl[1] : t[lc].sl[1];
	t[now].sr[1]=(t[rc].sum==t[rc].r-t[rc].l+1) ? t[rc].sum+t[lc].sr[1] : t[rc].sr[1];
	
	t[now].sm[0]=max(t[lc].sm[0],t[rc].sm[0]);
	t[now].sm[0]=max(t[now].sm[0],t[lc].sr[0]+t[rc].sl[0]);
	
	t[now].sl[0]=(t[lc].sum==0) ? (t[lc].r-t[lc].l+1+t[rc].sl[0]) : t[lc].sl[0];
	t[now].sr[0]=(t[rc].sum==0) ? (t[rc].r-t[rc].l+1+t[lc].sr[0]) : t[rc].sr[0]; 
	return;
}
inline Node merge(const Node &p1,const Node &p2)
{
	Node res;
	res.tag=-1;
	res.l=p1.l; res.r=p2.r;
	res.sum=p1.sum+p2.sum;
	res.sm[1]=max(p1.sm[1],p2.sm[1]);
	res.sm[1]=max(res.sm[1],p1.sr[1]+p2.sl[1]);
	
	res.sl[1]=(p1.sum==p1.r-p1.l+1) ? p1.sum+p2.sl[1] : p1.sl[1];
	res.sr[1]=(p2.sum==p2.r-p2.l+1) ? p2.sum+p1.sr[1] : p2.sr[1];
	return res;
}
inline void Addtag(const int &now,int key)
{
	if(key==0||key==1) {
		t[now].tag=key;
		t[now].sum=(t[now].r-t[now].l+1)*t[now].tag;
		t[now].sm[1]=t[now].sl[1]=t[now].sr[1]=t[now].sum;
		t[now].sm[0]=t[now].sl[0]=t[now].sr[0]=(t[now].r-t[now].l+1)*(t[now].tag^1);
	}
	else {
		if(t[now].tag==0||t[now].tag==1) 
			Addtag(now,t[now].tag^1);
		else {
			t[now].sum=(t[now].r-t[now].l+1)-t[now].sum;
			swap(t[now].sl[0],t[now].sl[1]);
			swap(t[now].sr[0],t[now].sr[1]);
			swap(t[now].sm[0],t[now].sm[1]);
			
			if(t[now].tag==-1) t[now].tag=2;
			else t[now].tag=-1;
		}
	}
	return;
}
inline void Pushdown(const int &now)
{
	if(t[now].l==t[now].r||t[now].tag==-1) 
		return;
	Addtag(lc,t[now].tag);
	Addtag(rc,t[now].tag);
	t[now].tag=-1;
	return;
}
void tag012(int now,const int &x,const int &y,const int &key)
{
	if(y<t[now].l||x>t[now].r) 
		return;
	if(x<=t[now].l&&t[now].r<=y) 
		return Addtag(now,key);
	Pushdown(now);
	tag012(lc,x,y,key);
	tag012(rc,x,y,key);
	Update(now);
	return;
}
Node query(int now,const int &x,const int &y)
{
	if(y<t[now].l||x>t[now].r) 
		return Node(-2);
	if(x<=t[now].l&&t[now].r<=y) 
		return t[now];
	Pushdown(now);
	Node res,p1,p2;
	p1=query(lc,x,y);
	p2=query(rc,x,y);
	
	if(p1.tag==-2) return p2;
	if(p2.tag==-2) return p1;
	res=merge(p1,p2);
	return res;
}
void print(int now)
{
	if(t[now].l==t[now].r) {
		printf("%d ",t[now].sum);
		return;
	}
	Pushdown(now);
	print(lc);
	print(rc);
	return;
}
int n,m;
int a[N];
void Build(int now,int l,int r)
{
	t[now].l=l;
	t[now].r=r;
	t[now].tag=-1;
	if(t[now].l==t[now].r) {
		t[now].sum=t[now].sl[1]=t[now].sr[1]=t[now].sm[1]=a[l];
		t[now].sl[0]=t[now].sr[0]=t[now].sm[0]=a[l]^1;
		return;
	}
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	Update(now);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	Build(1,1,n);
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		x++; y++;
		if(opt<=2) tag012(1,x,y,opt);
		else if(opt==3) printf("%d\n",query(1,x,y).sum);
		else printf("%d\n",query(1,x,y).sm[1]);
		
//		print(1); printf("\n");
	}
	return 0;
}


