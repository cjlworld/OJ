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
int n,m;
char job[N][12];
int toward[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++) 
		scanf("%d%s",&toward[i],job[i]);
	z=0;
	while(m--) {
		scanf("%d%d",&x,&y);
		if((toward[z]==0)^(x==1)) z=(z-y+n)%n;
		else z=(z+y)%n;
	}
	printf("%s",job[z]);
	return 0;
}

