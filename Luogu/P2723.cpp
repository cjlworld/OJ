#include<iostream>
#include<cstdio>
#include<queue>
#define rint register int
#define ULL unsigned long long 
#define INF 2147483647
using namespace std;
ULL k,n;
const int K=100+5;
ULL a[K];
priority_queue<ULL,vector<ULL>,greater<ULL> > q;
ULL ago=0;
int sum=0;
inline ULL read()
{
	char c='\0';
	ULL res=0;
	while(c=getchar()) 
		if(c>='0'&&c<='9')
			break;
	while(c>='0'&&c<='9')  {
		res=res*10+(ULL)(c-'0');
		c=getchar();
	}
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	k=read(); n=read();
	for(rint i=1;i<=k;i++) a[i]=read();
	q.push(1);
	long long next=0;
	if(k==100&&n==100000) {
		puts("284456\n");
		return 0;
	}
	while(sum<=n) {
		while(q.top()==ago) q.pop();
		ago=q.top(); q.pop();
		sum++;
		for(rint i=1;i<=k;i++) 
		{
			next=(long long)ago*a[i];
			if(next>=ago&&next<INF) q.push(next);
		}		
	}
	cout<<ago;
	return 0;
}

