#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=256;
int a[N];
int n,m;

bool dfs(int step,int depth)
{
	if(a[step-1]==n) return true;
	if(step==depth+1) return false;
	int i,j,t;
	vector<int> v;
	for(i=1;i<=step-1;i++) 
		for(j=1;j<=i;j++) {
			t=a[i]+a[j];
			if(t>a[step-1]&&t<=n) 
				v.push_back(t);
		}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	reverse(v.begin(),v.end());
	for(i=0;i<(int)v.size();i++) {
		a[step]=v[i];
		if(dfs(step+1,depth)) return true;
		a[step]=0;
	}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	a[1]=1;
	while(cin>>n,n) {
		m=1;
		while(!dfs(2,m)) m++;
		for(i=1;i<=m;i++) 
			printf("%d ",a[i]);
		printf("\n"); 
	}
	return 0;
}


