#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=10024;
vector<int> v;
int n,k;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		v.push_back(x);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	if(k>(int)v.size()||k<=0) printf("NO RESULT");
	else printf("%d",v[k-1]);
	return 0;
}

