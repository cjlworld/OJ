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
void print(T x)
{
	if(x<0) x=~x+1,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
	return;
}
template<class T>
inline void max(const T &x,const T &y)
{
	if(x>y) return x;
	else return y;
}
template<class T>
inline void min(const T &x,const T &y)
{
	if(x>y) return y;
	else return x;
}
template<class T>
inline void swap(T &x,T &y)
{
	T temp=x; x=y; y=temp;
	return;
}
}
#define rint register int 
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define min(x,y) FastIO::min(x,y) 
#define max(x,y) FastIO::max(x,y)
#define swap(x,y) FastIO::swap(x,y)
//=================================
//==========================================================
/*
第一行是一个整数 N，表示有 N 个国家；
第二行有 N 个空格隔开的整数，表示每个国家的初始喜欢度 δi ；
第三行是一个整数 M，表示有 M 条信息要处理；
第四行到最后，每行三个整数 x,l,r，
当 x=1 时询问游历国家 l 到 r 的开心值总和，就是 ∑ri=lδi ，
当 x=2 时国家 l 到 r 中每个国家的喜欢度 δi变为 √δi 。
*/
const int N=1e5+1e3;
int n,m;
LL a[N],c[N];
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
	int x,y,z,opt;
	read(n);
	for(i=1;i<=n+999;i++) 
		par[i]=i;
	for(i=1;i<=n;i++) {
		read(a[i]);
		update(i,a[i]);
		if(a[i]==1||a[i]==0) 
			par[i]=i+1; 
	}
	read(m);
	while(m--) {
		read(opt); read(x); read(y);
		if(opt==1) 
			print(sum(y)-sum(x-1)),putchar('\n');
		else {
			for(i=Find(x);i<=y;i=Find(i+1)) {
				if(a[i]==1||a[i]==0) {
					par[i]=Find(i+1);
					continue;
				}
				z=floor(sqrt(a[i]));
				update(i,z-a[i]);
				a[i]=z;
				if(a[i]==1||a[i]==0) 
					par[i]=Find(i+1);
			}
		}
	}
	return 0;
}

