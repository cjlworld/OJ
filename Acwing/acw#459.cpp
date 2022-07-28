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

// n*n 的矩阵外面一圈的数字数量为 4*(n-1) 
// 递推式 f(n,x,y)=f(n-2,x-1,y-1)+4*(n-1)
// 边界条件 1.f(n,1,y)=y, 2.f(n,x,n)=(n-1)+x, 3.f(n,n,y)=2*(n-1)+n-y+1, 4.f(n,x,1)=4*(n-1)-x+2; 

LL dp(int n,int x,int y)
{
	if(x==1) return y;
	else if(y==n) return (n-1)+x;
	else if(x==n) return 2*(n-1)+n-y+1;
	else if(y==1) return 4*(n-1)-x+2;
	else return dp(n-2,x-1,y-1)+4*(n-1);
}

int main()
{
//	freopen("1.in","r",stdin);
	int n,i,j;
	cin>>n>>i>>j;
	cout<<dp(n,i,j)<<endl;
	return 0;
}

