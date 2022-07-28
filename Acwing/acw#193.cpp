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

const int INF=1e9+5;
LL k;

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int A(LL a,LL b)
{
	if(k%gcd(a,b)) return INF;
	int res=0;
	while(a<k) a<<=1,res++;
	return res;
}

bool dfs(LL a,LL b,int u,int depth)
{
	if(a<b) swap(a,b);
	if((a==0&&b==0)||u-1+A(a,b)>depth) return false;
	else if(a==k||b==k) return true;
	
	if(dfs(a+a,b,u+1,depth)||dfs(a,a+a,u+1,depth)) return true;
	if(dfs(a+b,b,u+1,depth)||dfs(a,a+b,u+1,depth)) return true;
	if(dfs(labs(a-b),b,u+1,depth)||dfs(a,labs(a-b),u+1,depth)) return true;
	if(dfs(b+b,b,u+1,depth)||dfs(a,b+b,u+1,depth)) return true;
	
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>k;
	int depth=0;
	while(!dfs(1,0,1,depth)) depth++;
	cout<<depth<<endl;
	return 0;
}

