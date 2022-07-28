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

const int N=256,M=1e4+5;

int day,n,m;
int f[N]; // f[i] ��ʾ�ڵ�i�죬�����м���Ʒ�����������õ�������롣
int a[N][N]; // a[i][j] ��ʾ�� i ��� j �ּ���Ʒ�ļ۸�
int g[M];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	
	cin>>day>>n>>m;
	for(i=1;i<=day;i++) 
		for(j=1;j<=n;j++) 
			cin>>a[i][j];

	f[1]=m;
	for(i=2;i<=day;i++) {
		f[i]=f[i-1]; // ��һ��ɶҲ���ɡ� 
		
		memset(g,0,sizeof g); // �����ĸ������顣
		// �������� 
		for(j=1;j<=n;j++) {
			if(a[i][j]>a[i-1][j]&&a[i-1][j]<=f[i-1]) 
				x=a[i][j]-a[i-1][j],y=a[i-1][j]; // ��ֵ������� 
			else continue;
			
			for(k=y;k<=f[i-1];k++) 
				g[k]=max(g[k],g[k-y]+x);
		}
		f[i]=max(f[i],g[f[i-1]]+f[i-1]);
//		cout<<i<<" : "<<f[i]<<endl;
	}
	
	cout<<f[day]<<endl;
	return 0;
}

