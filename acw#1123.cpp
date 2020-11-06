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

const int N=1e5+5;

int main()
{
//	freopen("1.in","r",stdin);	
	double x,y;
	double a,b,c,d;
	double ans=0;
	scanf("%lf%lf",&x,&y);
	while(~scanf("%lf%lf%lf%lf",&a,&b,&c,&d)) 
		ans+=sqrt((a-c)*(a-c)+(b-d)*(b-d))*2.0/20000.0*60.0;
	LL times=round(ans);
	printf("%lld:%02lld\n",times/60,times%60);
	return 0;
}

