#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
const int N=1000010;
int c[N];
inline int lowbit(int n) 
{
	return n&(-n);
} 
inline void update(int x,int y)
{
	for(;x<=n;x+=lowbit(x)) c[x]+=y;
}
inline int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x)) res+=c[x];
	return res;
}
/*第一行2个整数n,m(n表示输入n个数，m表示m操作）
第二行n个整数
接下来每行三个数k,a,b(k=0,表示求子数列[a,b]的连续和；k=1,表示第a个数加b)。*/ 
int main()
{
	scanf("%d%d",&n,&m);
	int opt,x,k;
	int a,b;
	for(register int i=1;i<=n;i++) {
		scanf("%d",&x);
		update(i,x);
	}
	for(register int i=1;i<=m;i++) {
		scanf("%d%d%d",&opt,&a,&b);
		if(opt) update(a,b);
		else printf("%d\n",sum(b)-sum(a-1));
	}
	return 0;
}
