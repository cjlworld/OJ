#include<queue>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;
typedef pair<int,int> PII;

const int N=100+5;
int n,d;
int w[N][N],a[N];
PII c[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d",&n,&d);
	for(i=2;i<=n-1;i++) 
		scanf("%d",&a[i]);
	for(i=1;i<=n;i++) 
		scanf("%d%d",&c[i].first,&c[i].second);
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			w[i][j]=d*(abs(c[i].first-c[j].first)+abs(c[i].second-c[j].second));
	
	for(k=1;k<=n;k++) 
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) 
				if(i!=j&&j!=k&&i!=k)
					w[i][j]=min(w[i][j],w[i][k]+w[k][j]-a[k]);
	
	printf("%d\n",w[1][n]);
	return 0;
}

