#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1500+5;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
int n;
int root;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int f[N][2];
void Dp(int u)
{
	for(int i=one[u];i>0;i=Next[i]) 
		Dp(ver[i]);
	int v;
	for(int i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		f[u][1]+=min(f[v][0],f[v][1]);
		f[u][0]+=f[v][1];
	}
	f[u][1]++;
	return;
}
int dep[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	for(i=0;i<=n-1;i++) {
		scanf("%d%d",&x,&z);
		for(j=1;j<=z;j++) {
			scanf("%d",&y);
			dep[y]++;
			AddEdge(x,y);
		}
	}
	for(i=0;i<=n;i++) 
		if(dep[i]==0) {
			root=i;
			break;
		}
	Dp(root);
	cout<<min(f[root][0],f[root][1]);
	return 0;
}
