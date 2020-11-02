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

const int N=2000+5,V=305;
const double INF=1e10;

int n,m; // �γ�����������Ŀγ�����
int v,e; // ��������ͱߵ�������

int c[2][N]; // ԭ�������ŵĽ��ң�����Ľ��ҡ�
double K[N]; // ͨ���ĸ��� 
double w[V][V];
bool vis[N][N][2];
double f[N][N][2];

// Dp(x,y,z) ��ʾ [x,n] �������y�Σ�x�Ѿ�������/û���� ����õ���С����. 
double Dp(int x,int y,int st) // st=1 ������ 
{
	if(x==n) return 0.0;
	if(vis[x][y][st]) return f[x][y][st];
	vis[x][y][st]=true;
	double &u=f[x][y][st];
	double p1=INF,p2=INF;
	if(st==0) { // ��ǰû������ 
		p1=Dp(x+1,y,0)+w[c[0][x]][c[0][x+1]];
		if(y>=1) p2=Dp(x+1,y-1,1)+w[c[0][x]][c[1][x+1]]*K[x+1]+w[c[0][x]][c[0][x+1]]*(1-K[x+1]);
		return u=min(p1,p2);
	}
	else {
		p1=Dp(x+1,y,0)+w[c[1][x]][c[0][x+1]]*K[x]+w[c[0][x]][c[0][x+1]]*(1-K[x]);
		if(y>=1) p2=Dp(x+1,y-1,1)+w[c[1][x]][c[1][x+1]]*K[x]*K[x+1]
					+w[c[1][x]][c[0][x+1]]*K[x]*(1-K[x+1])
					+w[c[0][x]][c[1][x+1]]*(1-K[x])*K[x+1]
					+w[c[0][x]][c[0][x+1]]*(1-K[x])*(1-K[x+1]);
		
		return u=min(p1,p2);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	double z;
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(i=1;i<=n;i++) scanf("%d",&c[0][i]);
	for(i=1;i<=n;i++) scanf("%d",&c[1][i]);
	for(i=1;i<=n;i++) scanf("%lf",&K[i]);
	for(i=1;i<=v;i++) 
		for(j=1;j<=v;j++) 
			w[i][j]=INF;
	for(i=1;i<=v;i++) w[i][i]=0.0;
	for(i=1;i<=e;i++) {
		scanf("%d%d%lf",&x,&y,&z);
		w[x][y]=w[y][x]=min(w[x][y],z);
	}
	for(k=1;k<=v;k++) 
		for(i=1;i<=v;i++)
			for(j=1;j<=v;j++) 
				w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
	
	double ans=Dp(1,m,0);
	if(m>=1) ans=min(ans,Dp(1,m-1,1));
	printf("%.2lf\n",ans);
	return 0;
}
