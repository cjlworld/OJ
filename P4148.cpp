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

inline void tense(int &a,const int &b) { a=((a<b) ? a : b); }
inline void relax(int &a,const int &b) { a=((a>b) ? a : b); }

struct Node
{
	int x,y,val; // 当前点的坐标 (x,y) 和权值 val ;
	int sum; // 子树权值和。
	int L,R,U,D; // 当前子树内坐标的最值 
	int siz; // 子树内有多少个节点。 
	int judge; // 按什么划分两个子树。 
	int lc,rc; // 两个子树的编号。 
}t[N];
int idx,root;

void maintain(int now) // 维护信息，相当于 pushup 
{
	t[now].siz=t[t[now].lc].siz+t[t[now].rc].siz+1; // siz
	t[now].sum=t[t[now].lc].sum+t[t[now].rc].sum+t[now].val; //sum
	
	// 接下来维护四个边界的信息: L , R , D , U;
	 
	t[now].L=t[now].R=t[now].x;
	t[now].D=t[now].U=t[now].y;
	
	if(t[now].lc) {
		tense(t[now].L,t[t[now].lc].L);
		relax(t[now].R,t[t[now].lc].R);
		tense(t[now].D,t[t[now].lc].D);
		relax(t[now].U,t[t[now].lc].U);
	}
	if(t[now].rc) {
		tense(t[now].L,t[t[now].rc].L);
		relax(t[now].R,t[t[now].rc].R);
		tense(t[now].D,t[t[now].rc].D);
		relax(t[now].U,t[t[now].rc].U);		
	}
}

int NewNode(int x,int y,int val)
{
	idx++;
	t[idx].x=x;
	t[idx].y=y;
	t[idx].val=val;
	t[idx].lc=t[idx].rc=0;
	maintain(idx);
	return idx;
}

inline bool cmpx(const Node& a,const Node& b) { return a.x<b.x; }
inline bool cmpy(const Node& a,const Node& b) { return a.y<b.y; }

int build(int l,int r)
{
	if(l>r) return 0;
	int mid=(l+r)>>1;
	int mx1,mn1,mx2,mn2;
	mx1=mn1=t[l].x,mx2=mn2=t[l].y;
	
	for(int i=l+1;i<=r;i++) {
		relax(mx1,t[i].x);
		tense(mn1,t[i].x);
		relax(mx2,t[i].y);
		tense(mn2,t[i].y);
	}
	
	if(mx1-mn1>=mx2-mn2) {
		nth_element(t+l,t+mid,t+r+1,cmpx);
		t[mid].judge=1;
	}
	else {
		nth_element(t+l,t+mid,t+r+1,cmpy);
		t[mid].judge=2;
	}
	
	t[mid].lc=build(l,mid-1);
	t[mid].rc=build(mid+1,r);
	maintain(mid);
	return mid;
}

void insert(int& now,int id)
{
	if(!now) {
		now=id;
		return;
	}
	if(t[now].judge==1) {
		if(t[id].x<=t[now].x)
			insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	else {
		if(t[id].y<=t[now].y) 
			insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	maintain(now);
}

int query(int now,int l,int r,int d,int u)
{
	if(!now || r<t[now].L || l>t[now].R || u<t[now].D || d>t[now].U)
		return 0;
	if(t[now].L>=l && t[now].R<=r && t[now].D>=d && t[now].U<=u) 
		return t[now].sum;
//	printf("Query %d %d %d %d , and this node is %d %d %d %d\n"
//		,l,r,d,u,t[now].L,t[now].R,t[now].D,t[now].U);
	
	int res=0;
	if(t[now].x>=l && t[now].x<=r && t[now].y>=d && t[now].y<=u)
		res+=t[now].val;
	return res+query(t[now].lc,l,r,d,u)+query(t[now].rc,l,r,d,u);
}

int n;
int lastans;

int main()
{
//	freopen("1.in","r",stdin);
	int opt,x,y,z;
	int l,r,d,u;
	scanf("%d",&n);
	for(scanf("%d",&opt);opt!=3;scanf("%d",&opt)) {
		if(opt==1) {
			scanf("%d%d%d",&x,&y,&z);
			insert(root,NewNode(x^lastans,y^lastans,z^lastans));
			
			if(idx%30000==0)
			 	root=build(1,idx);
		}
		else {
			scanf("%d%d%d%d",&l,&d,&r,&u);
			printf("%d\n",lastans=query(root,l^lastans,r^lastans,d^lastans,u^lastans));
		}
	}
	return 0;
}

