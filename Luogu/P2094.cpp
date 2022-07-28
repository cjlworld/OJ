#include<queue>
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
priority_queue<int> Q;
int n,k;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		Q.push(x);
	}
	for(i=1;i<=n-1;i++) {
		x=Q.top(); Q.pop();
		y=Q.top(); Q.pop();
		Q.push((x+y)/k);
	}
	cout<<Q.top();
	return 0;
}

