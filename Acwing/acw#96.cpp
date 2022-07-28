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
int a[N]={0,1,3,5,9,13,17,25};

int main()
{
	for(int i=8;i<=12;i++) 
		a[i] = 1*a[i-1] + 0*a[i-2] + -5*a[i-3] + 7*a[i-4] + -2*a[i-5] + 10*a[i-6] + -10*a[i-7];
	for(int i=1;i<=12;i++) 
		printf("%d\n",a[i]);
	return 0;
}

