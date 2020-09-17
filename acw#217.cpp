#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=1e5+5,M=4*N;
int one[N],idx=1;
int ver[M],Next[M];
double edge[M];
inline void AddEdge(int a,int b,double c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int n,m;
int out[N];
double f[N];
bool vis[N];
double Dp(int x)
{
	int i,y;
	if(x==n) return 0;
	if(vis[x]) return f[x];
	vis[x]=true;
	// f[x]= \sum 1/k*(f[y]+edge[i])
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		f[x]+=Dp(y)+edge[i];
	}
	f[x]=f[x]/(out[x]*1.0);
	return f[x];
}

int main()
{
//	freopen("1.in","r",stdin);
    int i,x,y;
	double z;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++) {
    	scanf("%d%d%lf",&x,&y,&z);
    	AddEdge(x,y,z);
    	out[x]++;
	}
    printf("%.2f",Dp(1));
	return 0;	
}
