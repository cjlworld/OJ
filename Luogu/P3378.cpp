#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

priority_queue<int,vector<int>,greater<int> > q;

int n;

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	for(int i=1,opt,x;i<=n;i++) {
		scanf("%d",&opt);
		if(opt==1) {
			scanf("%d",&x);
			q.push(x);
		}
		else if(opt==2) printf("%d\n",q.top());
		else q.pop();
	}
	return 0;
}

