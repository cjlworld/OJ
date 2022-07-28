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

const int N=256;

int n,m; // n本书,m个人。 
int a[N];

bool check(int t)
{
	int i,sum=0,cnt=1;
	for(i=n;i>=1;i--) { //让后面的人多抄
		if(a[i]>t) return false;
		if(sum+a[i]>t) cnt++,sum=a[i];
		else sum+=a[i];
	}
	if(cnt>m) return false;
	else return true;
}

int ansl[N],ansr[N],top;

int main()
{
	int i;
	int L=0,R=0,mid; // 二分抄写最多的人抄写的页数。 
	// 保证 R-INF 可以, 0-L 不行。 
	scanf("%d%d",&n,&m);
	if(n==0) return 0; // 巨坑 
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		R+=a[i];
	}
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	int sum=0;
	ansr[top]=n;
	for(i=n;i>=1;i--) {
		if(sum+a[i]>R) {
			ansl[top]=i+1;
			ansr[++top]=i;
			sum=a[i];
		}
		else sum+=a[i];
	}
	ansl[top]=1;
	for(;top>=0;top--) 
		printf("%d %d\n",ansl[top],ansr[top]);
	return 0;
}

