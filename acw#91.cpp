#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=21,S=(1<<N)+5;
int a[N][N];
int f[S][N]; // f[i][j] ��ʾ�Ѿ�����  all x in {i} , ���ڵ���j�����·�� 
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,u;
	cin>>n;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++) 
			cin>>a[i][j];
	memset(f,0x3f,sizeof f);
	f[1][0]=0; // ����0��������0
	for(i=1;i<(1<<n);i++) {
		for(j=0;j<n;j++) { // ö�ٵ�ǰ״̬ f[ {i} ] [j]
			if(((i>>j)&1)==0) continue; // ���Ϸ� 
			u=i-(1<<j); // ��״̬ 
			for(k=0;k<n;k++) {
				if(((u>>k)&1)==0) continue;
				f[i][j]=min(f[i][j],f[u][k]+a[k][j]);
			}
		} 
	} 
	cout<<f[(1<<n)-1][n-1];
	return 0; 
}

