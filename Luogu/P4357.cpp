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
typedef pair<LL,LL> PLL;
typedef PLL Point;
typedef PLL Vector;

#define x first
#define y second

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); } 
template<class T>
inline void tense(T& a,const T& b) { a=((a<b) ? a : b); } 

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
LL length(Vector a) { return a.x*a.x+a.y*a.y; }
LL dist(Point a,Point b) { return length(a-b); }

const int N=2e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

struct Node
{
	int lc,rc;
	LL x,y;
	LL L,R,D,U;
}t[N];
int root;

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

int Build(int l,int r)
{
	if(l>r) return 0;	
	int mid=(l+r)>>1;	
	LL mx1=-INF,mn1=INF,mx2=-INF,mn2=INF;
	for(int i=l;i<=r;i++) {
		relax(mx1,t[i].x);
		tense(mn1,t[i].x);
		relax(mx2,t[i].y);
		tense(mn2,t[i].y);
	}
	
	if(mx1-mn1>=mx2-mn2) nth_element(t+l,t+mid,t+r+1,cmpx);
	else nth_element(t+l,t+mid,t+r+1,cmpy);
	t[mid].lc=Build(l,mid-1);
	t[mid].rc=Build(mid+1,r);
	Maintain(mid);
	return mid;
}

LL maxdist(int now,int x,int y)
{
	LL res=0;
	relax(res,dist(Point(t[now].L,t[now].D),Point(x,y)));
	relax(res,dist(Point(t[now].L,t[now].U),Point(x,y)));
	relax(res,dist(Point(t[now].R,t[now].D),Point(x,y)));
	relax(res,dist(Point(t[now].R,t[now].U),Point(x,y)));
	return res;
}

priority_queue<LL,vector<LL>,greater<LL> > q;
void query(int now,int x,int y)
{
	if(!now || maxdist(now,x,y)<=q.top()) return;
	LL d=dist(Point(t[now].x,t[now].y),Point(x,y));
	if(d>q.top()) q.pop(),q.push(d);
	
	LL dl=maxdist(t[now].lc,x,y),dr=maxdist(t[now].rc,x,y);
	
	if(dl>dr) {
		if(dl>q.top()) query(t[now].lc,x,y);
		if(dr>q.top()) query(t[now].rc,x,y);
	}
	else {
		if(dr>q.top()) query(t[now].rc,x,y);
		if(dl>q.top()) query(t[now].lc,x,y);	
	}
}

int n,K;

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i;
	
	scanf("%d%d",&n,&K);
	for(i=1;i<=n;i++) 
		scanf("%lld%lld",&t[i].x,&t[i].y);
	K*=2;
	for(i=1;i<=K;i++) q.push(0ll);
	
	root=Build(1,n);
	for(i=1;i<=n;i++) 
		query(root,t[i].x,t[i].y);
		
	printf("%lld\n",q.top());
	return 0;
}
