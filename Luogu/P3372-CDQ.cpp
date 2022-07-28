#include<set>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2e5+5;
struct Quiz
{
	int opt,x,y;
	LL k;
	int id;
	Quiz(int opt,int x,int y,int k,int id) : opt(opt),x(x),y(y),k(k),id(id) {}
	Quiz() {}	
}q[N];
int n,m;
LL ANS[N];
//struct Bit
//{
//	LL c[N]; 
//	LL res;
//	inline void lowbit(const int &x) { return x&(-x); }
//	inline void update(int x,const LL &y)
//	{
//		for(;x<=n;x+=lowbit(x)) 
//			c[x]+=y;
//		return;
//	}
//	inline LL sum(int x)
//	{
//		res=0;
//		for(;x>=1;x-=lowbit(x)) 	
//			res+=c[x];
//		return res;
//	}
//}C;
vector<int> v;
struct Node
{
	int l,r;
	mutable LL val;
	Node(int l,int r) : l(l),r(r),val(0) {}
	Node(int l) : l(l),r(l),val(0) {}
	Node() {}
	friend inline bool operator<(const Node &a,const Node &b)
	{
		return a.l<b.l;
	}
};
set<Node> S;
inline int getid(int x)
{
	return (int)(lower_bound(v.begin(),v.end(),x)-v.begin())+1;
}
void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	CDQ(l,mid);
	int i;
	v.clear(); S.clear();
	for(i=l;i<=r;i++) {
		v.push_back(q[i].x);
		v.push_back(q[i].y);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=0;i<(int)v.size();i++) {
		if(S.size()&&(--S.end())->r < v[i]-2) 
			S.insert(Node((--S.end())->r+1,v[i]-2));
		S.insert(Node(v[i]-1,v[i]-1));
		S.insert(Node(v[i],v[i]));
		S.insert(Node(v[i]+1,v[i]+1));
	}
	set<Node>::iterator it,itl;
	for(i=l;i<=mid;i++) {
		if(q[i].opt==1) {
			S.find(Node(q[i].x))->val+=q[i].k;
			S.find(Node(q[i].y+1))->val-=q[i].k;
		}
	}
	for(it=++S.begin(),itl=S.begin();it!=S.end();itl=it,it++) it->val+=itl->val;
	for(it=++S.begin(),itl=S.begin();it!=S.end();itl=it,it++) it->val=it->val*(it->r-it->l+1)+itl->val;
	for(i=mid+1;i<=r;i++) {
		if(q[i].opt==2) 
			ANS[q[i].id]+=S.find(q[i].y)->val-S.find(q[i].x-1)->val;
	}
	CDQ(mid+1,r);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,opt; LL z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%lld",&z);
		q[i]=Quiz(1,i,i,z,i);
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) scanf("%lld",&z);
		q[i+n]=Quiz(opt,x,y,z,i+n);
	}
	CDQ(1,n+m);
	for(i=n+1;i<=n+m;i++) 
		if(q[i].opt==2) 
			printf("%lld\n",ANS[q[i].id]);
	return 0;
}
