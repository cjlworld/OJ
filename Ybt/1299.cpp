#include<bitset>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=256,INF=1e8;
int n,k;
int f[N],g[N]; // f[i][j] ��ʾ ��ǰi��������ɵ����� %k==j �������.
// ��Ϊ���Ƿ��� mod k ÿһ��ͬ��ϵ����ֻҪ������һ���� 
// �����ù��������Ż����˵�һά 
int w[N];
int main()
{
	int i,j;
	scanf("%d%d",&n,&k);
	fill(f+1,f+k,-INF);
	for(i=1;i<=n;i++) {
		scanf("%d",&w[i]);
		memcpy(g,f,sizeof g);
		fill(f+1,f+k,-INF);
		for(j=k-1;j>=0;j--) 
			f[j]=max(g[j],g[((j-w[i])%k+k)%k]+w[i]);
	}
	cout<<f[0]<<endl;
	return 0;
}
