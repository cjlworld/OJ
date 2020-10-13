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

const int N=1e5+5;
const ULL P=1999999;
int n;
ULL a[7];

bool check(ULL *arr,ULL *brr)
{
	int i,j,k;
	for(i=1;i<=6;i++) {
		for(j=1;j<=6;j++) {
			for(k=1;k<=6;k++) 
				if(arr[(i+k-1-1)%6+1]!=brr[(j+k-1-1)%6+1]) break;
			if(k==7) return true;
		}
	}
	reverse(arr+1,arr+7);
	for(i=1;i<=6;i++) {
		for(j=1;j<=6;j++) {
			for(k=1;k<=6;k++) 
				if(arr[(i+k-1-1)%6+1]!=brr[(j+k-1-1)%6+1]) break;
			if(k==7) return true;
		}
	}
	return false;
}

struct Hashexcel
{
	int one[P],idx;
	ULL flow[N][7];
	int Next[N];
	void insert(ULL *arr,ULL x)
	{
		x=x%P;
		Next[++idx]=one[x];
		one[x]=idx;
		memcpy(flow[idx],arr,sizeof flow[idx]);
	}
	bool count(ULL *arr,ULL x)
	{
		for(int i=one[x%P];i;i=Next[i]) 
			if(check(flow[i],arr)) return true;
		return false;
	}
}H;
int main()
{
	int i,j;
	ULL x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		x=1,y=0;
		for(j=1;j<=6;j++) {
			scanf("%llu",&a[j]);
			x*=a[j],y+=a[j];
		}
		x=x+y;
		if(H.count(a,x)) {
			printf("Twin snowflakes found.\n");
			return 0;
		}
		else H.insert(a,x);
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}

