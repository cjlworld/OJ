#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
inline bool bad(const int &x)
{
	if(x==1||x==2||x==5) 
		return true;
	return false;
}
int n;
int ans,rest;
int a,b,c;
int main()
{
//	freopen("1.in","r",stdin); 
	cin>>n;
	if(bad(n)) {
		printf("-1\n");
		return 0;
	}
	ans=n/14;
	rest=n%14;
	if(bad(rest)) {
		rest+=14;
		ans--;
	}
	a=ans;
	c=rest/3-rest%3+ans;
	b=rest%3+ans;
	printf("%d %d %d\n",a,b,c);
 	return 0;
}

