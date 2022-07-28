#include<iostream>
#include<cstdio>
#include<set>
#include<queue>
#define LL long long
using namespace std;
priority_queue<int ,vector<int>, greater<int> > q; 
int n;
int main()
{
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&x);
		q.push(x);
	}
	int ago=-1;
	int cnt=0;
	for(int i=1;i<=n;i++) 
	{
		if(q.top()==ago) 
		{
			q.pop();
			cnt++;
			continue;
		}
		if(i!=1) printf("%d\n",cnt);
		printf("%d ",q.top());
		ago=q.top();
		q.pop();
		cnt=1;
	}
	printf("%d\n",cnt);
	return 0;
}

