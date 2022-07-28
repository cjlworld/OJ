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

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); }
template<class T>
inline void tense(T& a,const T& b) { a=((a<b) ? a : b); }

const int N=1e6+5,INF=0x3f3f3f3f;

struct Node
{
	int lc,rc;
	int x,y;
	int judge;
	int L,R,D,U;
}t[N];
int idx,root;

inline bool cmpx(const Node& a,const Node& b) { return a.x<b.x; }
inline bool cmpy(const Node& a,const Node& b) { return a.y<b.y; }

void Maintain(int x)
{
	t[x].L=t[x].R=t[x].x;
	t[x].U=t[x].D=t[x].y;
	
	if(t[x].lc) {
		tense(t[x].L,t[t[x].lc].L);
		relax(t[x].R,t[t[x].lc].R);
		tense(t[x].D,t[t[x].lc].D);
		relax(t[x].U,t[t[x].lc].U);
	}
	if(t[x].rc) {
		tense(t[x].L,t[t[x].rc].L);
		relax(t[x].R,t[t[x].rc].R);
		tense(t[x].D,t[t[x].rc].D);
		relax(t[x].U,t[t[x].rc].U);
	}
}

int build(int l,int r)
{
	if(l>r) return 0;
	int mid=(l+r)>>1;
	int mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;

	for(int i=l;i<=r;i++) {
		relax(mx1,t[i].x);
		tense(mn1,t[i].x);
		relax(mx2,t[i].y);
		tense(mn2,t[i].y);
	}

	if(mx1-mn1>=mx2-mn2) 
		nth_element(t+l,t+mid,t+r+1,cmpx),t[mid].judge=1;
	else nth_element(t+l,t+mid,t+r+1,cmpy),t[mid].judge=0;
	
	t[mid].lc=build(l,mid-1);
	t[mid].rc=build(mid+1,r);
	Maintain(mid);
	return mid;
}

void insert(int& now,int id)
{
	if(!now) {
		now=id;
		return;
	}
	if(t[now].judge) {
		if(t[id].x<=t[now].x) insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	else {
		if(t[id].y<=t[now].y) insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	Maintain(now);
}

int NewNode(int x,int y)
{
	idx++;
	t[idx].x=x,t[idx].y=y;
	t[idx].lc=t[idx].rc=0;
	t[idx].judge=(rand()&1);
	Maintain(idx);
	return idx;
}

int mindist(int now,int x,int y)
{
	int res=0;
	res+=max(0,t[now].L-x);
	res+=max(0,x-t[now].R);
	res+=max(0,t[now].D-y);
	res+=max(0,y-t[now].U);
	return res;
}

void query(int now,int x,int y,int& res)
{
	if(!now) return;
	tense(res,abs(t[now].x-x)+abs(t[now].y-y));
	int dl=mindist(t[now].lc,x,y);
	int dr=mindist(t[now].rc,x,y);
	
	if(dl<dr && dl<res) {
		query(t[now].lc,x,y,res);
		if(dr<res) query(t[now].rc,x,y,res);
	} 
	else if(dr<=dl && dr<res) {
		query(t[now].rc,x,y,res);
		if(dl<res) query(t[now].lc,x,y,res);
	}
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	srand((unsigned) time(0));

	int i;
	int opt,x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&x,&y);
		NewNode(x,y);
	}
	root=build(1,idx);
	int alpha=30000;
	
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) {
			insert(root,NewNode(x,y));
			if(idx%alpha==0)
				root=build(1,idx);
		}
		else {
			int ans=INF;
			query(root,x,y,ans);
			printf("%d\n",ans);
		}
		if(m%10000==0) cerr<<m<<" "<<clock()<<endl;
	}
	return 0;
}
