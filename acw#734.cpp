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

const int N=100+5,M=1e6+5;

int n,m,T;

struct Stone
{
	int S,E,L; // ʱ�䣬��ʼ������ÿ����ʧ������ 
	bool operator<(const Stone &t) const
	{
		return S*t.L<t.S*L;
	}
}a[N];

int f[M]; 
// f[i][j] ��ʾѡ����i������ʯ���Ѿ�����С��j�� ���ܻ�õ��������ֵ�� 
// ���е�һά���Ż��ˡ� 

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,t;
	scanf("%d",&T);
	for(t=1;t<=T;t++) {
		scanf("%d",&n);
		m=0;
		for(i=1;i<=n;i++) {
			scanf("%d%d%d",&a[i].S,&a[i].E,&a[i].L);
			m+=a[i].S;
		}
		sort(a+1,a+n+1);
		memset(f,0,sizeof f);
		for(i=1;i<=n;i++) 
			for(j=m;j>=a[i].S;j--) 
				f[j]=max(f[j],f[j-a[i].S]+a[i].E-a[i].L*(j-a[i].S));
		int ans=0;
		for(i=1;i<=m;i++) 
			ans=max(ans,f[i]);
		printf("Case #%d: %d\n",t,ans);
	}
	return 0;
}

