#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
int n;
int top,num;
LL ans=0;
void dfs(int step)
{
	if(step==2*n+1) {
		ans++;
		return;
	}
	if(top!=0) {
		top--;
		dfs(step+1);
		top++;
	}
	if(num!=0) {
		num--;
		top++;
		dfs(step+1);
		num++;
		top--;
	}
	return;
}
int main()
{
	freopen("1.out","w",stdout);
	for(n=1;n<=18;n++) {
		ans=0ll;
		top=0;
		num=n;
		dfs(1);
		cout<<ans<<"ll"<<",";
	}
	return 0;
}

