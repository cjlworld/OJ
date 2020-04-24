#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#define LL long long
using namespace std;
const int N=15+2;
const int S=(1<<N)+5;
const double INF=100000000.00;
int n;
struct node
{
	double x,y;
}a[N];
double w[N][N];
double dis(int x,int y)
{
	return sqrt((a[x].x-a[y].x)*(a[x].x-a[y].x)+(a[x].y-a[y].y)*(a[x].y-a[y].y));
}
double f[N][S]; //now -> N ; have S down
void print(int x)
{
	short bcc[N+3];
	memset(bcc,0,sizeof(bcc));
	int top=0;
	while(x) {
		top++;
		if(x&1) bcc[top]=1;
		else bcc[top]=0;	
		x>>=1;
	}
	for(int i=4;i>=1;i--) 
		putchar('0'+bcc[i]);
	putchar('\n');
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j,k,e,u,v,r;
	for(i=1;i<=n;i++) 
		scanf("%lf%lf",&a[i].x,&a[i].y);
//	for(i=1;i<=n;i++) 
//		printf("%.2f %.2f\n",a[i].x,a[i].y);
	for(i=1;i<=n;i++) {
		w[i][i]=0.0;
		for(j=i+1;j<=n;j++) {
			w[j][i]=w[i][j]=dis(i,j);
		}
	}
//	for(i=1;i<=n;i++,putchar('\n')) 
//		for(j=1;j<=n;j++) 
//			printf("%.2f ",w[i][j]);
	memset(f,127,sizeof f);
//	cout<<f[0][0]<<endl;
	for(i=1;i<=(1<<n)-1;i++) { // all S
		for(j=1;j<=n;j++) {
			if(!(i>>(j-1)&1)) continue;
			v=i^(1<<(j-1));
			for(k=1;k<=n;k++) {
				if(!(v>>(k-1)&1)) continue;
				f[j][i]=min(f[j][i],f[k][v]+w[k][j]);
			}
			if(v==0) 
				f[j][i]=min(f[j][i],dis(j,16));
//			print(i); 
//			printf(" %d from ",j);
//			print(v);
//			printf("%.2f\n",f[j][i]);
		}
	}
	const int s=(1<<n)-1;
	double ans=f[0][0]+1.1;
	for(i=1;i<=n;i++) {
		ans=min(ans,f[i][s]);
	}
	printf("%.2f\n",ans);
	return 0;
}

