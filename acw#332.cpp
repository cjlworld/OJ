#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2000+5;

int n,m,w;
int ap[N],bp[N],as[N],bs[N];
int f[N][N];
// f[i][j] 表示第i天有操作并且操作完后剩下j支股票的最大收益。
int g[N],q[N]; 
void relax(int &a,const int &b) { a=((a>b) ? a : b); }

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d%d",&n,&m,&w);
	for(i=1;i<=n;i++) 
		scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);
	memset(f,-0x3f,sizeof f);
	memset(g,-0x3f,sizeof g);
	g[0]=0;
	for(i=0;i<=n;i++) f[i][0]=0;
	
	int hh,tt;
	for(i=1;i<=n;i++) {
		// 把 i-w-1 天的决策加入集合 
		k=i-w-1;
		if(k>0) {
			for(j=0;j<=m;j++) 
				g[j]=max(g[j],f[k][j]);
		}
		// buy
		hh=tt=0,q[hh]=0;
		for(j=1;j<=m;j++) {
			while(hh<=tt&&q[hh]<j-as[i]) hh++;
			relax(f[i][j],g[q[hh]]+q[hh]*ap[i]-j*ap[i]);
			while(hh<=tt&&g[q[tt]]+q[tt]*ap[i]<=g[j]+j*ap[i]) tt--;
			q[++tt]=j;
		}
		// sell
		hh=tt=0,q[hh]=m;
		for(j=m-1;j>=0;j--) {
			while(hh<=tt&&q[hh]>j+bs[i]) hh++;
			relax(f[i][j],g[q[hh]]+q[hh]*bp[i]-j*bp[i]);
			while(hh<=tt&&g[q[tt]]+q[tt]*bp[i]<=g[j]+j*bp[i]) tt--;
			q[++tt]=j;
		}
			
//		for(j=0;j<=m;j++) {
//			for(r=max(j-as[i],0);r<j;r++) relax(f[i][j],g[r]+(r-j)*ap[i]);
//			for(r=j+1;r<=min(m,j+bs[i]);r++) relax(f[i][j],g[r]+(r-j)*bp[i]);
//		}
//		printf("f[%d][%d] = %d\n",i,j,f[i][j]);
	}
	
	int ans=0;
	for(i=0;i<=n;i++) 
		relax(ans,f[i][0]);
	printf("%d\n",ans);
//	printf("%d\n",f[n][0]);
	return 0;
}
