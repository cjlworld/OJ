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

const int N=16;
int a[N];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) a[i]=i;
	do {
		for(int i=1;i<=n;i++) 
			printf("%d ",a[i]);
		printf("\n");
	}while(next_permutation(a+1,a+n+1));
	return 0;
}

