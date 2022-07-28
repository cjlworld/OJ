#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rint register int
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
int n,m;
int a[N];
int sum[N];
int num[N];
inline void Add(int x)
{
	if(num[x]>=8) {
		num[x]++;
		return;
	}
	sum[num[x]]--;
	sum[++num[x]]++;
	return;
}
inline void Sub(int x)
{
	if(num[x]>=9) {
		num[x]--;
		return;
	}
	sum[num[x]]--;
	sum[--num[x]]++;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x;
	char opt;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		Add(a[i]);
	}
	scanf("%d",&m);
	while(m--) {
		for(opt=getchar();opt!='+'&&opt!='-';opt=getchar());
		scanf("%d",&x);
		if(opt=='+') Add(x);
		else Sub(x);
		if(sum[8]>=1||(sum[7]>0&&(sum[6]>0||sum[5]>0||sum[4]>0||sum[3]>0||sum[2]>0))||sum[7]>=2||sum[6]>=2||
			(sum[6]==1&&(sum[5]>0||sum[4]>0||sum[3]>0||sum[2]>0))||(sum[5]>=2)||(sum[5]==1&&sum[4]>=1)||(sum[4]>=2)
				||((sum[4]>=1||sum[5]>=1||sum[6]>=1||sum[7]>=1)&&(sum[3]+sum[2]>=2))) 
				puts("YES");
		else puts("NO"); 
	}
	return 0;
}
