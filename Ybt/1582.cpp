#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=6000+5;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int n;
int a[N];
int root;
int f[N][2];
void Dp(int u)
{
	for(int i=one[u];i>0;i=Next[i]) 
		Dp(ver[i]);
	int v;
	f[u][1]=a[u];
	for(int i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		f[u][1]+=f[v][0];
		f[u][0]+=max(f[v][0],f[v][1]);
	}
	return;
}
int dfs(int u)
{
	int res=0;
	for(int i=one[u];i>0;i=Next[i]) 
		res+=dfs(ver[i]);
	return res+1;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(i=1;i>=0;i++) {
		scanf("%d%d",&x,&y); //y is the manager of x
		if(x==0&&y==0) break; 
		AddEdge(y,x);
	}
	for(i=1;i<=n;i++) 
		if(dfs(i)==n) {
			root=i;
			break;
		}
	Dp(root);
	cout<<max(f[root][1],f[root][0]);
	return 0;
}

