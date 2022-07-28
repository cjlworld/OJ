#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n;
const int N=1e4+5;
const int M=1e6+5;
int one[N];
int dep[N];
int Next[2*M],ver[2*M];
int tot=0;
int c[N];
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int f[N];
queue<int> q;
inline void topsort()
{
	memset(f,0,sizeof(f));
	while(q.size()) q.pop();
	int x,y,z;
	int i,j;
	for(i=1;i<=n;i++) {
		if(dep[i]==0) {
			f[i]=c[i];
			q.push(i);
		}
	}	
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			f[y]=max(f[y],f[x]+c[y]);
			dep[y]--;
			if(dep[y]==0)
				q.push(y);
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	int x,y,z;
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		scanf("%d",&c[x]);
		y=1;
		while(y!=0) {
			scanf("%d",&y);
			if(y!=0) AddEdge(y,x),dep[x]++;
		}
	}
	topsort();
	int ans=0;
	for(i=1;i<=n;i++) 
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}

