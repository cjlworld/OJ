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
��һ����һ������ N����ʾ�� N �����ң�
�ڶ����� N ���ո��������������ʾÿ�����ҵĳ�ʼϲ���� ��i ��
��������һ������ M����ʾ�� M ����ϢҪ����
�����е����ÿ���������� x,l,r��
�� x=1 ʱѯ���������� l �� r �Ŀ���ֵ�ܺͣ����� ��ri=l��i ��
�� x=2 ʱ���� l �� r ��ÿ�����ҵ�ϲ���� ��i��Ϊ �̦�i ��
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

