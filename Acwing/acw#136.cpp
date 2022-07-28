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

const int N=1e5+5,INF=2e9+5;

set<int> S;
map<int,int> M;
int a[N];
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,p;
	set<int>::iterator it;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		x=INF;
		scanf("%d",&a[i]);
		if(i!=1) {
			it=S.lower_bound(a[i]);
			if(it!=S.end()&&*it-a[i]<x) x=*it-a[i],p=*it;
			if(it!=S.begin()) {
				it--;
				if(a[i]-*it<=x) x=a[i]-*it,p=*it;
			}
			printf("%d %d\n",x,M[p]);
		}
		M[a[i]]=i;
		S.insert(a[i]);
	}
		
	return 0;
}

