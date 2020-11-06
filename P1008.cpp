#include<bits/stdc++.h>
#define rint register int
using namespace std;
const int N=9+5;
const int End=9;
int n; 
bool b[N];
int a[N];
inline void check()
{
	int num1=0,num2=0,num3=0;
	for(rint i=1;i<=3;i++) {
		num1=num1*10+a[i];
		num2=num2*10+a[i+3];
		num3=num3*10+a[i+6];
	}
	if(num1>num2||num2>num3||num1>num3) return;
	if(num1*2==num2&&num1*3==num3) printf("%d %d %d \n",num1,num2,num3);
	return;
}
inline void dfs(int step)
{
	for(rint i=1;i<=9;i++) {
		if(b[i]) continue;
		a[step]=i;
		b[i]=true;
		if(step==End) check(); 
		else dfs(step+1);
		a[step]=0;
		b[i]=false;
	}
	return;
}
int main()
{
 	dfs(1);
	return 0;
}

