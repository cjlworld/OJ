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
struct Door
{
	char opt[10];
	int p;
}d[N];

int n,m,ans=0;

int calc(int u,int v)
{
	int i,t;
	for(i=1;i<=n;i++) {
		t=(d[i].p>>(u-1))&1;
		
		if(!strcmp(d[i].opt,"AND")) v=v&t;
		else if(!strcmp(d[i].opt,"XOR")) v=v^t;
		else v=v|t;
	}
	return v;
}

void dfs(int step,bool lt)
{
	if(step==0) return;
	
	int a=calc(step,1),b=calc(step,0);
	if((lt&&!(m>>(step-1)&1))||b>=a) 
		ans+=(b<<(step-1)),dfs(step-1,lt&&!(m>>(step-1)&1));
	else ans+=(a<<(step-1)),dfs(step-1,lt);
	
	return;
}

int count(int x)
{
	int len=1;
	while(x>>len) len++;
	return len;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int len=count(m);
	for(int i=1;i<=n;i++) {
		scanf("%s%d",d[i].opt,&d[i].p);
		len=max(len,count(d[i].p));
	}
	
	dfs(len,true);
	
	cout<<ans<<endl;
	return 0;
}

