#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
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

const LL MOD=1e9+7,IN6=166666668ll;
struct Node
{
	LL c,g,h;
	Node(LL c,LL g,LL h) : c(c),g(g),h(h) {}
	Node() {}
};
Node f[20][10][2][8][8];
// c[pos][num][bit][k] 表示 
//位数为 pos 的数 ,num = 0 前面数位无7，num=1 前面有7，整数的每一位加起来的和%7==bit,本身%7==k 的合法的数的个数； 
// g 表示同样限制条件下的数的和。 
// h 表示同样限制条件下的数的平方和 
// 当前状态已经把当前位计算了，也就是说每一位替下一位计算 
LL POW[100];
int dim[30];
void merge(Node &x,Node y,LL k,int pos)
{
	x.c=(x.c+y.c%MOD)%MOD;
	x.g=(x.g+y.g%MOD+POW[pos]%MOD*k%MOD*y.c%MOD)%MOD; 
	x.h=(x.h+y.h%MOD+
		y.c%MOD*k%MOD*k%MOD*POW[pos]%MOD*POW[pos]%MOD+
		y.g%MOD*POW[pos]%MOD*k%MOD*2%MOD)%MOD;
	return;
}

Node dfs(int pos,int sta,bool num,int bit,int k,bool lt)
{
	if(pos==1) return ((!bit||!k||num) ? Node(1,sta%MOD,sta*sta%MOD) : Node(0,0,0));
	Node &val=f[pos][sta][num][bit][k];
	if(!lt&&val.c!=-1) return val;
	
	int maxn=(lt) ? dim[pos-1] : 9;
	Node res(0,0,0);
	for(int i=0;i<=maxn;i++) 
		merge(res,dfs(pos-1,i,num||i==7,(bit+i)%7,(k*10+i)%7,lt&&i==maxn),sta,pos);
	if(!lt) val=res;
	return res;
}


LL count(LL n)
{
	memset(dim,0,sizeof dim);
	memset(f,-1,sizeof f);
	LL res=(n%MOD)*((n+1ll)%MOD)%MOD*((2ll*(n%MOD)+1ll)%MOD)%MOD*IN6%MOD;
	int tt=0;
	while(n) dim[++tt]=n%10,n/=10;
	
	for(int j=1;j<=tt;j++) {
		int maxn=((j==tt) ? dim[tt] : 9);
		for(int i=1;i<=maxn;i++) 
			res=(res-dfs(j,i,i==7,i%7,i%7,j==tt&&i==dim[tt]).h%MOD)%MOD;
	}
	return (res%MOD+MOD)%MOD;
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int T;
	LL l,r;

	POW[1]=1;
	for(int i=2;i<=40;i++) 
		POW[i]=POW[i-1]*10%MOD;

	cin>>T;
	while(T--) {
		cin>>l>>r;
		if(l==1) cout<<count(r)<<endl;
		else cout<<(count(r)-count(l-1)+MOD)%MOD<<endl;
	}
	return 0;
}
//	cout<<count(14)<<endl;
//	for(int i=1;i<=6;i++)
//		res-=dfs(tt+1,0,0,i,true)+dfs(tt+1,0,i,0,true);
//	res-=dfs(tt+1,0,0,0,true);

//LL gmul(LL x,LL k)
//{
//	LL res=0;
//	while(k) {
//		if(k&1) res=(res+x)%MOD;
//		x=(x+x)%MOD; k>>=1;
//	}	
//	return res;
//}
