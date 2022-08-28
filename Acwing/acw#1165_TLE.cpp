#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=2e5+5,n=26*26;

template<class T1,class T2> void relax(T1& x,const T2& y) { x=(x>y) ? x : y; }
template<class T1,class T2> void tense(T1& x,const T2& y) { x=(x<y) ? x : y; }

inline int id(char a,char b) { return (a-'a')*26+(b-'a'); }

int one[n],idx;
int ver[N],Next[N],edge[N];
inline void AddEdge(int a,int b,int c) 
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int m;

double dis[n];
int cnt[n],col[n];
bool vis[n];
queue<int> q;

bool spfa(const int& st,const double& t)
{
	int x,y; double z;
	
	// 优化：先记出连通块的大小(不用 n) 并 染色。
	int siz=1;
	q.push(st); col[st]=st;
	while(q.size()) {
		x=q.front(); q.pop();
		for(int i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(col[y]!=-1) continue;
			col[y]=st; q.push(y); siz++; 
		}
	}
	
	q.push(st); dis[st]=0; 
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false; 
		
		for(int i=one[x];~i;i=Next[i]) {
			y=ver[i]; z=t-edge[i];
			if(col[y]!=st) continue; // 染色剪枝。 同一颜色都是可以访问的。 
			
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				cnt[y]=cnt[x]+1;
				if(cnt[y]>=siz) return true;
				if(!vis[y]) q.push(y),vis[y]=true;
			}
		}
	}
	return false;
}

bool check(const double& t)
{	
	memset(col,-1,sizeof col);
	// 只要有到达过所有点就可以了，不一定要以每一点为源点做最短路。 
	// 因为倘若有负环，到达负环上的任意一点就能发现。 
	// 染色优化，可以证明不同源点出发经过同一点无用。
	// 同一点只要在任一源点经过一次即可。 
	
	// 因为每次访问的部分不冲突，初始化不用放在 spfa 里。 
	while(q.size()) q.pop();
	for(int i=0;i<n;i++) dis[i]=1e9;
	memset(vis,false,sizeof vis);
	memset(cnt,0,sizeof cnt);
	
	for(int i=0;i<n;i++) 
		if(col[i]==-1 && spfa(i,t)) 
			return true;
	return false; 
}

int w[n][n];

struct PII
{
	int x,y;
	PII(int x=0,int y=0) : x(x),y(y) {}
	bool operator<(const PII& other) const { return (x==other.x) ? (y<other.y) : (x<other.x); }
	bool operator==(const PII& other) const { return (x==other.x && y==other.y); }
};
vector<PII> edges;

int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d",&m),m) {
		string str;
		double L=1e9,R=0,mid;
		
		memset(one,-1,sizeof one); idx=0;
		// 优化同一起终点，保留最长串即可（优化边数）。 
		edges.clear();
		for(int i=1,x,y,z;i<=m;i++) {
			cin>>str;
			x=id(str[0],str[1]); y=id(str[str.length()-2],str[str.length()-1]); z=str.length();
			relax(w[x][y],z); edges.push_back(PII(x,y));
			relax(R,z); tense(L,z);
		}
		sort(edges.begin(),edges.end());
		edges.erase(unique(edges.begin(),edges.end()),edges.end());
		for(PII tmp;edges.size();edges.pop_back()) {
			tmp=edges.back(); 
			AddEdge(tmp.x,tmp.y,w[tmp.x][tmp.y]);
//			printf("(%d,%d)\n",tmp.x,tmp.y);
			w[tmp.x][tmp.y]=0;
		}
		
		if(!check(0)) {
			puts("No solution");
			continue;
		}
		
		while(L+0.01<R) {
			mid=(L+R)/2;
			if(check(mid)) L=mid;
			else R=mid;
		}
		printf("%.6lf\n",L);
	}
	return 0;
}

