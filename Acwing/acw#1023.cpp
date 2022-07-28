#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5000;
int n;
int a[N]={0,10,20,50,100};
LL f[N];
int main()
{
	cin>>n;
	int i,j;
	f[0]=1;
	for(i=1;i<=4;i++)
		for(j=1;j<=n;j++) 	
			if(j>=a[i])
				f[j]+=f[j-a[i]];
	cout<<f[n];
	return 0;
}

