#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
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

const int N=5e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int one[N],hs[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int h[],int a,int b,int c)
{
	Next[idx]=h[a]; ver[idx]=b; edge[idx]=c; h[a]=idx++;
}

int dfn[N],times;
int dep[N],up[N][26];
LL fm[N][26];

void deal_first(int x,int fa,int cost)
{
	dfn[x]=++times;
	dep[x]=dep[fa]+1;
	up[x][0]=fa;
	fm[x][0]=cost;

	for(int i=1;i<=25 && up[up[x][i-1]][i-1];i++) {
		up[x][i]=up[up[x][i-1]][i-1];
		fm[x][i]=min(fm[x][i-1],fm[up[x][i-1]][i-1]);
	}
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x,edge[i]);
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int d=dep[x]-dep[y],i=0;d;i++,d>>=1)
		if(d&1) x=up[x][i];
	if(x==y) return x;
	for(int i=25;i>=0;i--) {
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i];
	}
	return up[x][0];
}

int query(int x,int y)
{
	LL res=INF;
	if(dep[x]<dep[y]) swap(x,y);
	for(int d=dep[x]-dep[y],i=0;d;i++,d>>=1)
		if(d&1) tense(res,fm[x][i]),x=up[x][i];
	if(x==y) return res;
	for(int i=20;i>=0;i--)
		if(up[x][i]!=up[y][i]) {
			tense(res,fm[x][i]);
			tense(res,fm[y][i]);
			x=up[x][i]; y=up[y][i];
		}
	tense(res,fm[x][0]);
	tense(res,fm[y][0]);
	return res;
}

bool cmp(int a,int b) { return dfn[a]<dfn[b]; }

int n,m;
int vn; // 虚树中的节点个数。 
int vir[N]; // 虚树中的节点标号。 
bool st[N]; // 关键点。
 
void build_vir()
{
	static int stk[N],top; 
	idx=0;
	stk[top=0]=1; hs[1]=-1;
	sort(vir+1,vir+vn+1,cmp);
	vn=unique(vir+1,vir+vn+1)-vir-1;
	
	int tn=vn;
	for(int i=1;i<=tn;i++) st[vir[i]]=true;
	for(int i=1;i<=tn;i++) {
		int x=vir[i],z=lca(x,stk[top]);
		if(z==stk[top]) stk[++top]=x;
		else {
			for(;top && dep[stk[top-1]]>=dep[z];top--) 
				AddEdge(hs,stk[top-1],stk[top],query(stk[top-1],stk[top]));
				
			if(stk[top]!=z) {
				AddEdge(hs,z,stk[top],query(stk[top],z)); top--;
				stk[++top]=vir[++vn]=z; 
			}
			stk[++top]=x;
		}
	} 
	for(int i=0;i<top;i++) AddEdge(hs,stk[i],stk[i+1],query(stk[i],stk[i+1]));
}

LL f[N];
void Dp(int x)
{
	if(st[x]) f[x]=INF;
	else f[x]=0;
	
	for(int i=hs[x],y;~i;i=Next[i]) {
		y=ver[i];
		Dp(y);
		f[x]+=min(f[y],(LL)edge[i]);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(one,x,y,z);
		AddEdge(one,y,x,z);
	}
	deal_first(1,0,0);
	
	memset(hs,-1,sizeof hs);
	scanf("%d",&m);
	while(m--) {
		scanf("%d",&vn);
		for(i=1;i<=vn;i++)
			scanf("%d",&vir[i]);
		build_vir();
		Dp(1);
		for(i=1;i<=vn;i++) hs[vir[i]]=-1,st[vir[i]]=false;
		
		printf("%lld\n",f[1]);	
	}
	return 0;
}

