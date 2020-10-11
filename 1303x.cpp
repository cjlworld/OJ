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

const int N=10+5;
int T,m,n; // ��m�ֳ�n��
LL f[N][N][N]; // f[k][i][j] ��ʾ �Ѿ��ֵ���k������,����i��,��Ϊj�ķ�������
LL g[N][N][N]; // g[k][i][j] = sum(f[1][i][j]---f[k][i][j])
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>T;
	while(T--) {
		cin>>m>>n;
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		f[0][0][0]=1,g[0][0][0]=1;
		for(k=1;k<=m;k++) {
			for(i=0;i<=n;i++)	
				for(j=0;j<=m;j++) 
					g[k][i][j]=g[k-1][i][j];
			for(i=1;i<=n;i++) 
				for(j=k;j<=m;j++) {
					f[k][i][j]=g[k][i-1][j-k];
					g[k][i][j]+=f[k][i][j]; // ǰ׺���Ż� 
				}
		}
		LL ans=0;
		for(k=1;k<=m;k++) 
			for(i=1;i<=n;i++) 
				ans+=f[k][i][m];
		cout<<ans<<endl;
	}
	return 0;
}

