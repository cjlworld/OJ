#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
namespace FastIO
{
template<class T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	bool sign=false;
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
template<class T>
inline void print(T x)
{
	if(x<0) putchar('-'),x=-x;
	int bcc[21];
	int top=0;
	while(x>0) {
		bcc[++top]=x%10;
		x=x/10;
	}
	while(top>0) {
		putchar('0'+bcc[top]);
		top--;
	}
	putchar(10);
	return;
}
}
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
//==========================================================
/*
第一行是一个整数 N，表示有 N 个国家；
第二行有 N 个空格隔开的整数，表示每个国家的初始喜欢度 δi ；
第三行是一个整数 M，表示有 M 条信息要处理；
第四行到最后，每行三个整数 x,l,r，
当 x=1 时询问游历国家 l 到 r 的开心值总和，就是 ∑ri=lδi ，
当 x=2 时国家 l 到 r 中每个国家的喜欢度 δi变为 √δi 。
*/
const int N=2e5+5;
int n,m;
LL a[N];
LL c[N];
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,LL y) 
{
	for(;x<=n;x+=lowbit(x)) 
		c[x]+=y;
	return;
}
inline LL sum(int x)
{
	LL res=0;
	for(;x>=1;x-=lowbit(x)) 
		res+=c[x];
	return res;
}
int par[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	int opt;
	int cnt=0;
	while(cin>>n) {
		cnt++;
		printf("Case #%d:\n",cnt);
		memset(par,0,sizeof par);
		memset(a,0,sizeof a);
		memset(c,0,sizeof c);
		for(i=1;i<=n;i++) 
			par[i]=i;
		for(i=1;i<=n;i++) {
			read(a[i]);
			update(i,a[i]);
		}
		read(m);
		while(m--) {
			read(opt); read(x); read(y);
			if(x>y) swap(x,y);
			if(opt==1) print(sum(y)-sum(x-1));
			else {
				i=x;
				while(i<=y) {
					j=Find(i);
					if(j>y) break;
					z=floor(sqrt(a[j]));
					update(j,z-a[j]);
					a[j]=z;
					if(a[j]==1||a[j]==0) 
						par[j]=Find(j+1);
					i=j+1;
				}
			}
		}
	}
	return 0;
}

