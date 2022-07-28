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
		for(i=63;i>=0;i--) { // 这是以第 i 为最高位的基，存在第 k 行。 
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
		
		reverse(a,a+k); // 改成从低位到高位排,因为二进制是从低位到高位的。 
//		for(i=0;i<k;i++) printf("%lld ",a[i]);
//		puts("");
		// 如果 k<n 则可以生成 0 , 否则不行。
		// k 个基两合生成 2^k-1 个非零的值，( 因为不能全不选) 
		// 若可以生成 0 , 则总共生成 2^k. 
		scanf("%d",&m);
		while(m--) {
			scanf("%lld",&x);
			if(x>(1ll<<k)-1+(k<n)) { // 别忘了 1ll 
				puts("-1");
				continue;
			}
			if(k<n) x--; 
			// 这是因为如果可以生成 0 的话，
			// 则 1th 与 0 对， 2th 与 1 对 ..... 
			// 于是整体下移一格。 
//			printf("now print the %lld th\n",x); 
			LL ans=0;
			for(i=0;i<k;i++) 
				if((x>>i)&1) ans^=a[i];
			printf("%lld\n",ans);
		}
	}
	return 0;
}

