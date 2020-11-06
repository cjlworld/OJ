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

int main()
{
	int i,j,n;
	cin>>n;
	for(i=0;i<(1<<n);i++) {
		for(j=0;j<n;j++) 
			if((i>>j)&1) printf("%d ",j+1);
		printf("\n");
	}
	return 0;
}

