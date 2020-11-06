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

int n,m;

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

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int len=log2(m)+1,i,a,b;
	for(i=1;i<=n;i++) {
		scanf("%s%d",d[i].opt,&d[i].p);
		len=max(len,(int)log2(d[i].p)+1);
	}
	int ans=0,now=0; // ans 答案 ; now 已经选择的二进制的位组成的能力值 
	for(i=len;i>=1;i--) {
		a=calc(i,1),b=calc(i,0);
		if(now+(1<<(i-1))>m||b>=a) 
			ans+=(b<<(i-1));
		else now+=(1<<(i-1)),ans+=(a<<(i-1));
	}
	
	cout<<ans<<endl;
	return 0;
}

