#include<bitset>
#include<cstdio>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=5e7+3e6;
bitset<N> bs;
int n,k;

int main()
{
	register int i,x,sum=0;
	bs[0]=1;
	scanf("%d%d",&n,&k);
	while(n--) {
		scanf("%d",&x);
		bs|=bs<<x;
		sum+=x;
	}
	for(i=sum/k*k;i>=0;i-=k)  
		if(bs[i]) {
			printf("%d\n",i);
			return 0;
		}
	return 0;
}
