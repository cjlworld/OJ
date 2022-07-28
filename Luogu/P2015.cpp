#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=100+5;
const int M=256;
int one[N];
int ver[M],edge[M],Next[M];
int tot=0;
inline void AddEdge(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
int n,k;
int a[N];
int f[N][N];
void Dp(int u,const int &fa,int apple)
{
	for(int i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			Dp(ver[i],u,edge[i]);
	int v;
	f[u][0]=0;
	f[u][1]=apple;		
	for(int i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(ver[i]==fa) continue;
		for(int j=k;j>=2;j--) {
			for(int e=1;e<=j-1;e++) {
				f[u][j]=max(f[u][j],f[u][j-e]+f[v][e]);
			}
		}
	}
	return;
}
void print()
{
	int i,j;
	cout<<endl;
	for(i=1;i<=n;i++) {
		for(j=0;j<=k;j++) {
			cout<<f[i][j]<<" ";
		}
		cout<<endl;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&k);
	k++;
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dp(1,0,0);
//	print();
	cout<<f[1][k];
	return 0;
}

