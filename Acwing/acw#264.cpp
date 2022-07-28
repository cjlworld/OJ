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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=4e5+5,M=1e6+5,INF=0x3f3f3f3f;

int one[N],idx;
int Next[N],ver[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int n,m;
int siz[N];
bool vis[N];

int Getsiz(int x,int fa)
{
	int i,y,res=1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]||y==fa) continue;
		res+=Getsiz(y,x);
	}
	return res;
}

void Gravity(int x,int fa,int Ts,int &Root)
{
	int i,y,ms=0;
	siz[x]=1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]||y==fa) continue;
		Gravity(y,x,Ts,Root);
		siz[x]+=siz[y];
		ms=max(ms,siz[y]);
	}	
	ms=max(ms,Ts-siz[x]);
	if(ms<=Ts/2) Root=x;
}

int f[M];

vector<PII> vs;
vector<int> del;

void Work(int x,int fa,int dist,int race)
{
	if(dist>m) return;
	vs.push_back(PII(dist,race));
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]||y==fa) continue;
		Work(y,x,dist+edge[i],race+1);
	}
}

int calc(int x)
{
	if(vis[x]) return INF;
	
	int i,j,y,res=INF;
	PII t;
	Gravity(x,-1,Getsiz(x,-1),x);
	vis[x]=true;
    
    f[0]=0;
    del.clear();
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(vis[y]) continue;
		
		vs.clear();
		Work(y,x,edge[i],1);
		for(j=vs.size()-1;j>=0;j--) {
			t=vs[j];
			res=min(res,t.second+f[m-t.first]);
		}
		for(j=vs.size()-1;j>=0;j--) {
			t=vs[j];
			f[t.first]=min(f[t.first],t.second);
			del.push_back(t.first);
		}
	}
	for(i=del.size()-1;i>=0;i--) f[del[i]]=INF;
	
	for(i=one[x];i;i=Next[i]) res=min(res,calc(ver[i]));
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	memset(f,0x3f,sizeof f);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	int ans=calc(1);
	if(ans==INF) printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}

