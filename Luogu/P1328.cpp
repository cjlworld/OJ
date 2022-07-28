#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int NN=21;
int f[NN][NN]=
{
{0,0,1,1,0},
{1,0,0,1,0},
{0,1,0,0,1},
{0,0,1,0,1},
{1,1,0,0,0}
};
const int N=256;
int a[N],b[N];
int ans1,ans2;
int n,na,nb;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	scanf("%d%d%d",&n,&na,&nb);
	for(i=1;i<=na;i++) 
		scanf("%d",&a[i]);
	for(i=1;i<=nb;i++) 
		scanf("%d",&b[i]);
	for(i=na+1;i<=n;i++) 
		a[i]=a[i-na];
	for(i=nb+1;i<=n;i++) 
		b[i]=b[i-nb];
	for(i=1;i<=n;i++) {
		ans1+=f[a[i]][b[i]];
		ans2+=f[b[i]][a[i]];
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}

