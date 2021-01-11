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

const int N=2e5+5;

int T;
int n,m;

LL a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	LL x;

	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++) {
		printf("Case #%d:\n",Case);
		scanf("%d",&n);
		for(i=0;i<n;i++) 
			scanf("%lld",&a[i]);
		int k=0;
		for(i=63;i>=0;i--) { // �����Ե� i Ϊ���λ�Ļ������ڵ� k �С� 
			for(j=k;j<n;j++) 
				if((a[j]>>i)&1) {
					swap(a[j],a[k]);
					break;
				}
				
			if(!((a[k]>>i)&1)) continue;
			for(j=0;j<n;j++) 
				if(j^k && (a[j]>>i)&1) 
					a[j]^=a[k];
			k++;
			if(k==n) break;
		}
		
		reverse(a,a+k); // �ĳɴӵ�λ����λ��,��Ϊ�������Ǵӵ�λ����λ�ġ� 
//		for(i=0;i<k;i++) printf("%lld ",a[i]);
//		puts("");
		// ��� k<n ��������� 0 , �����С�
		// k ������������ 2^k-1 �������ֵ��( ��Ϊ����ȫ��ѡ) 
		// ���������� 0 , ���ܹ����� 2^k. 
		scanf("%d",&m);
		while(m--) {
			scanf("%lld",&x);
			if(x>(1ll<<k)-1+(k<n)) { // ������ 1ll 
				puts("-1");
				continue;
			}
			if(k<n) x--; 
			// ������Ϊ����������� 0 �Ļ���
			// �� 1th �� 0 �ԣ� 2th �� 1 �� ..... 
			// ������������һ�� 
//			printf("now print the %lld th\n",x); 
			LL ans=0;
			for(i=0;i<k;i++) 
				if((x>>i)&1) ans^=a[i];
			printf("%lld\n",ans);
		}
	}
	return 0;
}

