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

// 理论基础：两个奇数码问题的局面相互可达当且仅当二者转化为n^2-1序列(0不要)的逆序对的奇偶性相同。
 
const int N=250000+5;
int n;
int a[N],b[N];

struct Bits
{
	int c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	int Sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
	void clear()
	{
		memset(c,0,sizeof c);
	}
}C;

int calc(int *arr)
{
	int res=0;
	C.clear();
	for(int i=1;i<=n;i++) {
		if(arr[i]==0) continue;
		res=(res+C.Sum(n)-C.Sum(arr[i]))&1;
		C.Update(arr[i],1);
	}
	return res&1;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	while(scanf("%d",&n)==1) {
		n=n*n;
		for(i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		for(i=1;i<=n;i++)
			scanf("%d",&b[i]);
		x=calc(a),y=calc(b);
		if(x^y) printf("NIE\n");
		else printf("TAK\n");
	}
	return 0;
}

