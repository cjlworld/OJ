//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
//#pragma GCC optimize("-fgcse-lm")
//#pragma GCC optimize("-fipa-sra")
//#pragma GCC optimize("-ftree-pre")
//#pragma GCC optimize("-ftree-vrp")
//#pragma GCC optimize("-fpeephole2")
//#pragma GCC optimize("-ffast-math")
//#pragma GCC optimize("-fsched-spec")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("-falign-jumps")
//#pragma GCC optimize("-falign-loops")
//#pragma GCC optimize("-falign-labels")
//#pragma GCC optimize("-fdevirtualize")
//#pragma GCC optimize("-fcaller-saves")
//#pragma GCC optimize("-fcrossjumping")
//#pragma GCC optimize("-fthread-jumps")
//#pragma GCC optimize("-funroll-loops")
//#pragma GCC optimize("-fwhole-program")
//#pragma GCC optimize("-freorder-blocks")
//#pragma GCC optimize("-fschedule-insns")
//#pragma GCC optimize("inline-functions")
//#pragma GCC optimize("-ftree-tail-merge")
//#pragma GCC optimize("-fschedule-insns2")
//#pragma GCC optimize("-fstrict-aliasing")
//#pragma GCC optimize("-fstrict-overflow")
//#pragma GCC optimize("-falign-functions")
//#pragma GCC optimize("-fcse-skip-blocks")
//#pragma GCC optimize("-fcse-follow-jumps")
//#pragma GCC optimize("-fsched-interblock")
//#pragma GCC optimize("-fpartial-inlining")
//#pragma GCC optimize("no-stack-protector")
//#pragma GCC optimize("-freorder-functions")
//#pragma GCC optimize("-findirect-inlining")
//#pragma GCC optimize("-fhoist-adjacent-loads")
//#pragma GCC optimize("-frerun-cse-after-loop")
//#pragma GCC optimize("inline-small-functions")
//#pragma GCC optimize("-finline-small-functions")
//#pragma GCC optimize("-ftree-switch-conversion")
//#pragma GCC optimize("-foptimize-sibling-calls")
//#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("-funsafe-loop-optimizations")
//#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<ctime>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#define LL long long
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
template <class I>
inline void print(I x) {
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

#define rint register int 
const int N=2500+5;
const LL INF=0x7fffffff;
int one[N];
int ver[2*N],Next[2*N];
LL edge[2*N];
int tot=0;
inline void AddEdge(const int &a,const int &b,const LL &c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
//=======================================
int n,m,k;
vector<LL> dis[105];
vector<bool> vis[105];
struct cmp
{
	inline bool operator()(const pair<int,int> &a,const pair<int,int> &b) 
	{
		return (dis[a.first][a.second]>dis[b.first][b.second])^(rand()%50<1);
	}
};
priority_queue< pair<int,int> , vector< pair<int,int> > ,cmp > q;
#define vtp(x,y) {	while(dis[x].size()<=(unsigned)y)  dis[x].push_back(INF); while(vis[x].size()<=(unsigned)y+1) vis[x].push_back(false);}
inline void SPFA(const int &st)
{
	rint x,y,u;
	register LL z;
	rint i;
	q.push(pair<int,int>(st,0));
	vtp(st,1);
	dis[st][0]=0;
//	for(i=0;i<dis[st].size();i++) 
//		printf("%lld\n",dis[st][i]);
	vis[st][0]=1;
	while(q.size()) {
//		x=q.front().first; 
		x=q.top().first;
		y=q.top().second;
		q.pop();
		vis[x][y]=false;
		for(i=one[x];i>0;i=Next[i]) {
			u=ver[i]; z=edge[i];
			vtp(u,y);
			if(dis[u][y]>dis[x][y]+z) {
				dis[u][y]=dis[x][y]+z;
				if(!vis[u][y]) {
					vis[u][y]=true;
					q.push(pair<int,int>(u,y));
				}
			}
		}
		if(y+1>k) continue;
		for(i=one[x];i>0;i=Next[i]) {
			u=ver[i]; z=edge[i];
			if(z<=0) continue;
			vtp(u,y+1);
			if(dis[u][y+1]>dis[x][y]-z) {
				dis[u][y+1]=dis[x][y]-z;
				if(!vis[u][y+1]) {
					vis[u][y+1]=true;
					q.push(pair<int,int>(u,y+1));
				}
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	srand(time(0));
	rint i;
	rint x,y;
	register LL z;
	read(n); read(m); read(k);
	for(i=1;i<=m;i++) {
		read(x); read(y); read(z);
		AddEdge(x,y,z);
	}
	SPFA(1);
	register LL ans=INF;
	for(i=0;(unsigned)i<dis[n].size();i++) 
		ans=min(ans,dis[n][i]);
	print(ans);
	FastIO::flush();
	return 0;
}

