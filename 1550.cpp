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
��һ����һ������ N����ʾ�� N �����ң�
�ڶ����� N ���ո��������������ʾÿ�����ҵĳ�ʼϲ���� ��i ��
��������һ������ M����ʾ�� M ����ϢҪ����
�����е����ÿ���������� x,l,r��
�� x=1 ʱѯ���������� l �� r �Ŀ���ֵ�ܺͣ����� ��ri=l��i ��
�� x=2 ʱ���� l �� r ��ÿ�����ҵ�ϲ���� ��i��Ϊ �̦�i ��
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

