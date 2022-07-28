#include<set>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
LL seed,vmax;
inline LL rnd()
{
	LL ret = seed;
    seed = (seed * 7ll + 13ll ) % 1000000007ll;
    return ret;
}
LL Mod;
const int N=1e5+5;
int n,m;
inline LL quickpow(LL x,LL k,const LL &MOD)
{
	LL res=1ll;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1; 
	}
	return res%MOD;
}
namespace ODT
{
struct Node
{
	int l,r;
	mutable LL val;
	Node(int l,int r,LL val) : l(l),r(r),val(val) {}
	Node(int l) : l(l),r(-1),val(0) {}
	Node() {}
	friend inline bool operator<(const Node &a,const Node &b)
	{
		return a.l<b.l;
	}
};
set<Node> S;
#define IT set<Node>::iterator
Node tmp;
inline IT split(const int &pos)
{
	IT it=S.lower_bound(Node(pos));
	if(it!=S.end()&&it->l==pos) 
			return it;
	it--;
	tmp=*it;
	S.erase(it);
	S.insert(Node(tmp.l,pos-1,tmp.val));
	return S.insert(Node(pos,tmp.r,tmp.val)).first;
}
inline void assign(const int &l,const int &r,const LL &val)
{
	IT itr=split(r+1),itl=split(l);
	S.erase(itl,itr);
	S.insert(Node(l,r,val));
	return;
}
inline void modify(const int &l,const int &r,const LL &key)
{
	IT itr=split(r+1),itl=split(l);
	for(IT it=itl;it!=itr;it++) 
		it->val=it->val+key;
	return;
}
vector< pair<LL,int> > V;
inline LL findkth(const int &l,const int &r,const int &rank)
{
	V.clear();
	IT itr=split(r+1),itl=split(l);
	for(IT it=itl;it!=itr;it++) 
		V.push_back(pair<LL,int>(it->val,it->r-it->l+1));
	sort(V.begin(),V.end());
	int sum=0;
	for(rint i=0;i<(signed)V.size();i++) {
		sum+=V[i].second;
		if(sum>=rank) 
			return V[i].first;
	}
	return V.back().first;
}
inline LL getpows(const int &l,const int &r,const LL &k,const LL &MOD)
{
	LL res=0;
	IT itr=split(r+1),itl=split(l);
	for(IT it=itl;it!=itr;it++) 
		res=(res+quickpow(it->val%MOD,k,MOD)*((LL)(it->r-it->l+1ll))%MOD)%MOD;
	return res;
}
#undef IT
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y,opt;
	LL z;
	scanf("%d%d%lld%lld",&n,&m,&seed,&vmax);
	for(i=1;i<=n;i++) 
		ODT::S.insert(ODT::Node(i,i,rnd()%vmax+1ll));
	for(i=1;i<=m;i++) {
		//=============================
        opt=rnd()%4+1;
        x=rnd()%n+1;
        y=rnd()%n+1;
        if(x>y) 
        	swap(x,y);
        if(opt==3) 
        	z=rnd()%(y-x+1)+1ll;
        else z=rnd()%vmax+1ll;
        if(opt==4) 
        	Mod=rnd()%vmax+1;
		//==============================
        if(opt==1) ODT::modify(x,y,z);
        else if(opt==2) ODT::assign(x,y,z);
        else if(opt==3) printf("%lld\n",ODT::findkth(x,y,z));
        else if(opt==4) printf("%lld\n",ODT::getpows(x,y,z,Mod)%Mod);
	}
	return 0;
}

