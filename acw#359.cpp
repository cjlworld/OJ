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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=2e6+5,INF=0x3f3f3f3f;

int one[N],idx;
int Next[N],ver[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
}

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

int f[N][2];
void Dp(int x,int fa,int canall)
{
	int tmp=-INF;
	f[x][0]=0; f[x][1]=1;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp(y,x,canall);
		
		f[x][0]+=max(f[y][0],f[y][1]);
		if(f[y][0]>=f[y][1]) {
			tmp=0;
			f[x][1]+=f[y][0];
		}
		else {
			tmp=max(tmp,f[y][0]-f[y][1]);
			f[x][1]+=f[y][1];
		}
	}
	if(canall!=x) f[x][1]+=tmp;
}

int n;
vector<PII> roots;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x;
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		if(Find(i)==Find(x)) 	
			roots.push_back(PII(i,x));
		else AddEdge(x,i),par[Find(x)]=Find(i);
	}
	
	int ans=0,res;
	for(i=0;i<(int)roots.size();i++) {
		PII u=roots[i];
		
		Dp(u.first,0,-1);
		res=f[u.first][1];
		Dp(u.first,0,u.second);
		res=max(res,f[u.first][0]);
		ans+=res;
	}
	
	printf("%d\n",ans);
	return 0;
}

