#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef PII Point;
typedef pair<double,double> Line;

#define x first
#define y second

const int N=1e5+5,INF=0x3f3f3f3f,MOD=39989;

inline double f(const Line& a,const double& x) { return x*a.x+a.y; }
inline double intsec(const Line& a,const Line& b)  { return (b.y-a.y)/(a.x-b.x); }

Line a[N];
int idx;

int t[4*N];

#define lc (now<<1)
#define rc (now<<1|1)

void Update(int now,int id,int x,int y,int l,int r)
{
	int mid=(l+r)>>1;
	Line& val=a[id],cur=a[t[now]];
	if(x<=l && r<=y) {
		if(f(val,l)<=f(cur,l) && f(val,r)<=f(cur,r)) return;
		else if(f(val,l)>=f(cur,l) && f(val,r)>=f(cur,r)) 
			return t[now]=id,void();
		
		double xs=intsec(val,cur);
		if(f(val,l)>f(cur,l)) {
			if(xs<=mid) Update(lc,id,x,y,l,mid);
			else Update(rc,t[now],x,y,mid+1,r),t[now]=id;
		}
		else {
			if(xs>mid) Update(rc,id,x,y,mid+1,r); // ?
			else Update(lc,t[now],x,y,l,mid),t[now]=id;
		}
		return;
	}
	if(x<=mid) Update(lc,id,x,y,l,mid);
	if(y>mid) Update(rc,id,x,y,mid+1,r);
}

int query(int now,int pos,int l,int r)
{
	if(l==r) return t[now];
	int mid=(l+r)>>1,res=t[now],tmp;
	
	if(pos<=mid) tmp=query(lc,pos,l,mid);
	else tmp=query(rc,pos,mid+1,r);
	
	if(f(a[tmp],pos)>f(a[res],pos) || (f(a[tmp],pos)==f(a[res],pos) && tmp<res)) res=tmp;
	return res;
}

int n,lastans;

int main()
{
	int x,opt;
	
	a[0]=Line(0,-INF);
	scanf("%d",&n);
	while(n--) {
		scanf("%d",&opt);
		if(opt==0) {
			scanf("%d",&x);
			x=(x+lastans-1)%MOD+1;
			printf("%d\n",lastans=query(1,x,1,MOD));
		} 
		else {
			PII u,v;
			scanf("%d%d%d%d",&u.x,&u.y,&v.x,&v.y);
			u.x=(u.x+lastans-1)%MOD+1;
			v.x=(v.x+lastans-1)%MOD+1;
			u.y=(u.y+lastans-1)%((int)1e9)+1;
			v.y=(v.y+lastans-1)%((int)1e9)+1;
			
			if(u.x>v.x) swap(u,v);
			
			if(u.x==v.x) a[++idx]=Line(0,max(u.y,v.y));
			else {
				double k=1.0*(u.y-v.y)/(u.x-v.x);
				double b=u.y-k*u.x;
				a[++idx]=Line(k,b);
			}
			
			Update(1,idx,u.x,v.x,1,MOD);
		}
	}
	return 0;
}

