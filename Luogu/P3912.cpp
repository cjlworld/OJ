#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=1e8+5,M=1e7+5;

int p[M],tot;
bool tag[N];

void prime(int n)
{
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int n;
	cin>>n;
	prime(n);
	cout<<tot<<endl;
	return 0;
}

