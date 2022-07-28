#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=351;
const int M=41;
int f[N][M][M][M];
int cost[N];
int card[M];
int Dp(int step,int a,int b,int c,int d)
{
	if(step<1||a<0||b<0||c<0||d<0) 
		return -1;
	int &ans=f[step][a][b][c];
	if(ans!=-1)
		return ans;
	ans=max(ans,Dp(step-1,a-1,b,c,d));
	ans=max(ans,Dp(step-2,a,b-1,c,d));
	ans=max(ans,Dp(step-3,a,b,c-1,d));
	ans=max(ans,Dp(step-4,a,b,c,d-1));
	ans+=cost[step];
	return ans;
}
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d",&cost[i]);
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		card[x]++;
	}
	memset(f,-1,sizeof f);
	f[1][0][0][0]=cost[1];
	cout<<Dp(n,card[1],card[2],card[3],card[4]);
	return 0;
}

