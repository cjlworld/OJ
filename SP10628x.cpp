#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rint register int
using namespace std;namespace FastIO
{const int _SIZE = (1 << 21) + 1;inline char NextChar(){static char ibuf[_SIZE];static char *iS,*iT;if(iS==iT) iS=ibuf,iT=iS+fread(ibuf,1,_SIZE,stdin);return (iS == iT ? EOF : *iS++);
}template <class T>inline void read(T &x) {static char c;static bool sign;x=0;sign=false;for (c=NextChar();c<'0'||c>'9';c=NextChar())if (c=='-') sign=true;for (;c>='0'&&c<='9';c=NextChar()) x=(x<<1)+(x<<3)+(c&15);if(sign) x=-x;
}char obuf[_SIZE];char *oS=obuf,*oT=obuf+_SIZE-1;inline void flush() {fwrite(obuf,1,oS-obuf,stdout);oS=obuf;
}inline void putc(const char &x) {*oS++=x;if(oS==oT) flush();
}template <class T>inline void print(T x) {static char qu[50];static int qr;if (!x) {putc('0');return;}if (x<0) putc('-'),x=-x;for(qr=1;x;qr++,x/=10) qu[qr]=x%10+'0';for(qr--;qr>=1;qr--) putc(qu[qr]);}struct Flusher_ {~Flusher_() { flush(); }}io_flusher_;
}using FastIO::read;using FastIO::print; 
#define enter FastIO::putc('\n')
const int N=5e5+5,INF=0x3f3f3f3f,SQ=2000;struct Block
{int num[SQ],L[SQ],R[SQ];int t[N],F[N];int size,k;void Build(rint n){size=sqrt(n);
k=n/size+(n/size>0);rint i,j;for(i=1;i<=k;i++) {L[i]=R[i-1]+1;R[i]=i*size;}R[k]=N-1;for(i=1;i<=k;i++) for(j=L[i];j<=R[i];j++) F[j]=i;
	}inline void Update(rint val,rint key)
{t[val]+=key;num[F[val]]+=key;}inline int count(rint l,rint r){rint i,res=0;if(F[l]==F[r]) {for(i=l;i<=r;i++) res+=t[i];
return res;}for(i=l;i<=R[F[l]];i++) res+=t[i];for(i=F[l]+1;i<=F[r]-1;i++) res+=num[i];for(i=L[F[r]];i<=r;i++) res+=t[i];return res;
	}inline int Getkth(rint kth)
{rint now=0,pblock,i;for(i=1;i<=k;i++) {if(now+num[i]>=kth) break;now+=num[i];}pblock=i;
for(i=L[pblock];i<=R[pblock];i++) {if(now+t[i]>=kth) return i;now+=t[i];}return R[pblock];}
}B;int n,m;int one[N],idx;int Next[N],ver[N];inline void AddEdge(rint a,rint b)
{Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}int dep[N],son[N],top[N],fat[N],bts[N],lb[N],rb[N],tot;
void dfs(rint x,rint fa){static int siz[N];fat[x]=fa;dep[x]=dep[fa]+1;siz[x]=1;for(rint i=one[x],y;~i;i=Next[i]) {y=ver[i];if(y==fa) continue;dfs(y,x);siz[x]+=siz[y];if(siz[y]>siz[son[x]]) son[x]=y;}}
void dfs(rint x){if(son[fat[x]]==x) top[x]=top[fat[x]];else top[x]=x;bts[lb[x]=++tot]=x;for(rint i=one[x],y;~i;i=Next[i]) {y=ver[i];if(y==fat[x]) continue;dfs(y);
	} bts[rb[x]=++tot]=x;
}int lca(rint x,rint y)
{while(top[x]!=top[y]) { if(dep[top[x]]<dep[top[y]]) swap(x,y);x=top[x]; x=fat[x];
	}if(dep[x]<dep[y]) return x;else return y;
}int siz;struct Query
{int l,r,kth,acs;int id;inline bool operator<(const Query& t) const{if(l/siz!=t.l/siz) return l<t.l;else return ((l/siz)&1)^(r<t.r);}
Query(int l=0,int r=0,int kth=0,int acs=0,int id=0) :l(l),r(r),kth(kth),acs(acs),id(id) {}
}q[N];int ans[N],a[N];bool st[N];inline void Add(rint pos) {if(st[pos]) B.Update(a[pos],-1); else B.Update(a[pos],1);st[pos]^=1;}vector<int> nums;
int main()
{rint i,k;int x,y,z;read(n); read(m);
for(i=1;i<=n;i++) {read(a[i]);nums.push_back(a[i]);
	}sort(nums.begin(),nums.end());nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) a[i]=upper_bound(nums.begin(),nums.end(),a[i])-nums.begin();memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {read(x); read(y);AddEdge(x,y);
	}dfs(1,0); dfs(1);for(i=1;i<=m;i++) {read(x); read(y); read(k);if(dep[x]>dep[y]) swap(x,y);z=lca(x,y);if(z==x) q[i]=Query(lb[x],lb[y],k,0,i);else q[i]=Query(rb[x],lb[y],k,z,i);
	}siz=sqrt(2*n);sort(q+1,q+m+1);int hh=1,tt=0;B.Build(nums.size()+1);
	for(i=1;i<=m;i++) {while(hh>q[i].l) Add(bts[--hh]);while(tt<q[i].r) Add(bts[++tt]);while(hh<q[i].l) Add(bts[hh++]);while(tt>q[i].r) Add(bts[tt--]);if(q[i].acs) Add(q[i].acs);ans[q[i].id]=B.Getkth(q[i].kth);if(q[i].acs) Add(q[i].acs);
	}for(i=1;i<=m;i++) print(nums[ans[i]-1]),enter;
	return 0;
}
