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

const int N=60000+5;
bitset<N> f;
int a[10];
int sum;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	while(scanf("%d",&a[1])==1) {
		sum=0;
		for(i=2;i<=6;i++) 	
			scanf("%d",&a[i]);
		for(i=1;i<=7;i++) sum+=i*a[i];
		if(sum==0) break;
		
		if(sum&1) {
			printf("Can't\n");
			continue;
		}
		f.reset();
		f[0]=1;
		for(i=1;i<=6;i++) {
			for(j=1;j<a[i];j<<=1) {
				f|=f<<(j*i);
				a[i]-=j;
			}
			f|=f<<(a[i]*i);
		}
		if(f[sum/2]) printf("Can\n");
		else printf("Can't\n");
	}
	return 0;
}

