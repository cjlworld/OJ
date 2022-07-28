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

const int N=256,INF=1e9+5;
int n,m;
int a[N][N],f[N][N];
// f[step][tot] = w
// step ѡ��ǰ 1 ~ step-1 �ķֹ�˾������ѡstep����ѡ��tot���豸 
// ���ӯ��w 
int cnt[N][N];

void print(int x,int y)
{
	if(x==0) return;
	print(x-1,y-cnt[x][y]);
	printf("%d %d\n",x,cnt[x][y]);
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			cin>>a[i][j];
	
	memset(f,0xcf,sizeof f);
	f[0][0]=0;
	
	for(i=1;i<=n;i++) 
		for(j=0;j<=m;j++) // ѡ���ѡ�˼����豸 
			for(k=0;k<=j;k++) { // ��һ���ֹ�˾ѡ�˼����豸 
				if(f[i-1][j-k]+a[i][k]>=f[i][j]) {
					f[i][j]=f[i-1][j-k]+a[i][k];
					cnt[i][j]=k;
				}
			}
	int ans=0;
	for(i=m;i>=1;i--)
		if(f[n][i]>f[n][ans]) ans=i;
	cout<<f[n][ans]<<endl;
	print(n,ans);
	return 0;
}
// ���������й������ַ���û��spj�� 
