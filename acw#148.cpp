#include<queue>
#include<cstdio>
#include<iostream>
#define rint register int
typedef long long LL;
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;
int n; 
int main()
{
//	freopen("1.in","r",stdin);
	int x,y;
	LL ans=0;
	cin>>n;
	while(n--) {
		cin>>x;
		q.push(x);
	}
	while(q.size()>=2) {
		x=q.top(); q.pop();
		y=q.top(); q.pop();
		q.push(x+y);
		ans+=(LL)(x+y);
	}
	cout<<ans;
	return 0;
}


