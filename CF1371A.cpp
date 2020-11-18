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

int T,n;
int main()
{
	cin>>T;
	while(T--) {
		cin>>n;
		cout<<(n-1)/2+1<<endl;
	}
	return 0;
}

