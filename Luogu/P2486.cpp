#include<set>
#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
namespace FastIO
{
const int _SIZE = (1 << 21) + 1;
char ibuf[_SIZE],obuf[_SIZE];
char *iS,*iT;
char c;
char qu[55];
char *oS=obuf,*oT=oS+_SIZE-1;
bool _sign=false;
int qr;
// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, _SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
// print the remaining part
inline void flush() 
{
    fwrite(obuf,1,oS-obuf,stdout);
    oS=obuf;
    return;
}
// putchar
inline void putc(const char &x) 
{
    *oS++=x;
    if(oS==oT)
        flush();
    return;
}
inline char getc()
{
	return gc();
}
// input a signed integer
template <class T>
inline void read(T &x) 
{
	x=0;
	_sign=false;
    for (c=gc();c<'0'||c>'9';c=gc())
        if (c=='-')
            _sign=true;
    for (;c>='0'&&c<='9';c=gc()) 
		x=(x<<1)+(x<<3)+(c&15);
    x=(_sign) ? (~x+1) : x;
    return;
}
// print a signed integer
template <class T>
inline void print(T x) {
    if (!x) {
    	putc('0');
    	return;
	}
    if (x<0)
        putc('-'),x=~x+1;
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
    return;
}
// no need to call flush at the end manually!
struct Flusher_ 
{
    ~Flusher_() { flush(); }
}io_flusher_;
}  // namespace io
using FastIO::read;
using FastIO::print;
using FastIO::putc;
using FastIO::getc;
//===================================
const int N=1e5+5;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//==================================
int son[N];
int dep[N],sum[N];
int fa[N];
void dfs1(int now,const int &father)
{
	fa[now]=father;
	dep[now]=dep[father]+1;
	sum[now]=1;
	rint i,v;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(v==father) 
			continue;
		dfs1(v,now);
		sum[now]+=sum[v];
		if(sum[v]>sum[son[now]]) 
			son[now]=v;
	}
	return;
}
int dfn[N],times=0;
int org[N];
int top[N];
void dfs2(int now)
{
	dfn[now]=++times;
	org[times]=now;
	if(son[fa[now]]==now) 
		top[now]=top[fa[now]];
	else top[now]=now;
	if(son[now]) 
		dfs2(son[now]);
	else return;
	rint i,v;
	for(i=one[now];i>0;i=Next[i]) {
		v=ver[i];
		if(v==son[now]||v==fa[now]) 
			continue;
		dfs2(v);
	}
	return;
}
//=========================================
struct Node
{
	int l,r;
	int col;
	Node(int l,int r,int col) : l(l),r(r),col(col) {}
	Node(int l) : l(l),r(-1),col(-1) {}
	Node() {}
	friend inline bool operator<(const Node &x,const Node &y)
	{
		return x.l<y.l;
	}
};
set<Node> S;
#define IT set<Node>::iterator
inline IT split(int pos)
{
	IT it=S.lower_bound(Node(pos));
 	if (it!=S.end()&&it->l==pos)  
        return it;
    --it; 
    int L=it->l,R=it->r; 
    LL V=it->col; 
    S.erase(it);  
    S.insert(Node(L,pos-1,V)); 
    return S.insert(Node(pos,R,V)).first; 
}
inline void assign_val(int l,int r,int val)
{
    IT itr=split(r+1),itl=split(l); 
    S.erase(itl, itr);  
    S.insert(Node(l,r,val)); 
    return;
}
int b[N][3];
int cnt=0;
inline pair< int,pair<int,int> > count(int l,int r)
{
	IT itr=split(r+1),itl=split(l);
	int res=0;
	int last=-1,col=-1;
	cnt=0;
	bool flag=false;
	for(IT it=itl;it!=itr;it++) {
		if(it->col==col) flag=true;
		else {
			if(flag) {
				cnt++;
				b[cnt][1]=last;
				b[cnt][2]=(--it)->r; it++;
				b[cnt][0]=col;
				flag=false;
			}
			last=it->l;
			col=it->col;
			res++;
		}
	}
	for(rint i=1;i<=cnt;i++) 
		assign_val(b[i][1],b[i][2],b[i][0]);
	return make_pair(res,make_pair(itl->col,(--itr)->col));	
}	
//inline pair< int,pair<int,int> > count(int l,int r)
//{
//	IT itr=split(r+1),itl=split(l);
//	rint res=0;
//	rint col=-1;
//	for(IT it=itl;it!=itr;it++) {
//		if(it->col!=col) {
//			col=it->col;
//			res++;
//		}
//	}
//	return make_pair(res,make_pair(itl->col,(--itr)->col));	
//}	
int a[N];
inline void paint(int x,int y,const int &key)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		assign_val(dfn[top[x]],dfn[x],key);
		x=top[x]; x=fa[x];
	}
	if(dep[x]<dep[y]) 
		swap(x,y);
	assign_val(dfn[y],dfn[x],key);
	return;
}
inline int query(int x,int y)
{
	if(x==y) return 1;
	int res=0;
	int lx=-1,ly=-1;
	IT itl,itr;
	pair<int,pair<int,int> > z;
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) {
			z=count(dfn[top[x]],dfn[x]);
			if(lx==z.second.second) 
				z.first--;
			lx=z.second.first;
			x=top[x]; x=fa[x];
		}
		else {
			z=count(dfn[top[y]],dfn[y]);
			if(ly==z.second.second) 
				z.first--;
			ly=z.second.first;
			y=top[y]; y=fa[y];
		}
		res+=z.first;
	}
	if(dep[x]>dep[y]) {
		z=count(dfn[y],dfn[x]);
		if(lx==z.second.second) 
			z.first--;
		if(ly==z.second.first)
			z.first--;
	}
	else {
		z=count(dfn[x],dfn[y]);
		if(ly==z.second.second)
			z.first--; 
		if(lx==z.second.first)
			z.first--;
	}	
	res+=z.first;
	return res;
}
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x,y,z;
	char opt;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	dfs1(1,0);
	dfs2(1);
	for(i=1;i<=n;i=j+1) {
		for(j=i;j+1<=n&&a[org[i]]==a[org[j+1]];j++); 
			S.insert(Node(i,j,a[org[j]]));
	}		
	while(m--) {
		for(opt=getc();opt!='Q'&&opt!='C';opt=getc());
		if(opt=='C') {
			read(x); read(y); read(z);
			paint(x,y,z);
		}
		else {
			read(x); read(y);
			print(query(x,y)); putc('\n');
		}
	}
	return 0;
}

