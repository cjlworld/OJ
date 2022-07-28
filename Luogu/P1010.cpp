#include<bits/stdc++.h>
#define rint register int
using namespace std;
const int End=15;
const int N=40000+5;
int n;
inline void code(int c,bool flag)
{
	if(c==0) { printf("0"); return; }
	for(int i=End;i>=0;i--) {
		int po=(1<<i);
		if(po>c) continue;
		c=c-po;
		if(i==1) { 
			if(flag) printf("2"),flag=false;
			else printf("+2");
			continue;
		}
		if(flag) { printf("2("); flag=false; }
		else printf("+2(");
		code(i,true); 
		printf(")");
	}
	return;
}
int main()
{
	scanf("%d",&n);
	code(n,true);
	return 0;
}

